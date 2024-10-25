#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 100

// Function to execute a command with optional redirection and piping
void execute_command(char *cmd) {
    char *args[MAX_ARGS];      
    char *args_pipe[MAX_ARGS];   
    char *input_file = NULL;     
    char *output_file = NULL;   
    int pipe_fd[2];              
    int has_pipe = 0;            

    // Tokenize the command to handle redirection and pipes
    char *token = strtok(cmd, " ");
    int i = 0;

    // Parse the command for redirection operators and pipe
    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            input_file = strtok(NULL, " ");
            if (input_file == NULL) {
                fprintf(stderr, "Error: Missing input file after '<'\n");
                return;
            }
        } else if (strcmp(token, ">") == 0) {
            output_file = strtok(NULL, " ");
            if (output_file == NULL) {
                fprintf(stderr, "Error: Missing output file after '>'\n");
                return;
            }
        } else if (strcmp(token, "|") == 0) {
            has_pipe = 1;  // Indicate that there's a pipe
            token = strtok(NULL, " ");
            int j = 0;
            while (token != NULL) {
                args_pipe[j++] = token;
                token = strtok(NULL, " ");
            }
            args_pipe[j] = NULL; // Terminate args_pipe array
            break;
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  // Terminate args array

    // If there’s a pipe, handle piped commands
    if (has_pipe) {
        // Create a pipe and check for errors
        if (pipe(pipe_fd) == -1) {
            perror("Error creating pipe");
            exit(EXIT_FAILURE);
        }

        // First child process for the command before the pipe
        pid_t pid1 = fork();
        if (pid1 < 0) {
            perror("Error creating first child process");
            exit(EXIT_FAILURE);
        } else if (pid1 == 0) {
            // Redirect input if an input file is specified
            if (input_file) {
                int in_fd = open(input_file, O_RDONLY);
                if (in_fd < 0) {
                    perror("Error opening input file");
                    exit(EXIT_FAILURE);
                }
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            // Redirect stdout to the pipe
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[0]);
            close(pipe_fd[1]);

            // Execute the first command
            execvp(args[0], args);
            perror("Error executing command before pipe");
            exit(EXIT_FAILURE);
        }

        // Parent process: close write end of the pipe and wait for the first child
        close(pipe_fd[1]);
        waitpid(pid1, NULL, 0);

        // Second child process for the command after the pipe
        pid_t pid2 = fork();
        if (pid2 < 0) {
            perror("Error creating second child process");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            // Redirect stdin from the pipe
            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[0]);

            // Redirect output if an output file is specified
            if (output_file) {
                int out_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (out_fd < 0) {
                    perror("Error opening output file");
                    exit(EXIT_FAILURE);
                }
                dup2(out_fd, STDOUT_FILENO);
                close(out_fd);
            }

            // Execute the second command
            execvp(args_pipe[0], args_pipe);
            perror("Error executing command after pipe");
            exit(EXIT_FAILURE);
        }

        // Parent process: close read end of the pipe and wait for the second child
        close(pipe_fd[0]);
        waitpid(pid2, NULL, 0);
    } else {
        // No pipe: Execute a single command with optional redirection
        pid_t pid = fork();
        if (pid < 0) {
            perror("Error creating child process");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Redirect input if an input file is specified
            if (input_file) {
                int in_fd = open(input_file, O_RDONLY);
                if (in_fd < 0) {
                    perror("Error opening input file");
                    exit(EXIT_FAILURE);
                }
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }

            // Redirect output if an output file is specified
            if (output_file) {
                int out_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (out_fd < 0) {
                    perror("Error opening output file");
                    exit(EXIT_FAILURE);
                }
                dup2(out_fd, STDOUT_FILENO);
                close(out_fd);
            }

            // Execute the command
            execvp(args[0], args);
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }

        // Parent process: wait for the child to finish
        waitpid(pid, NULL, 0);
    }
}

int main() {
    char cmd[MAX_CMD_LEN];  // Buffer to hold the command input by the user

    // Main loop for shell prompt
    while (1) {
        printf("PUCITshell@/home/arif/:- ");
        
        // Get command input from user
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            break; // Exit on EOF
        }
        
        // Remove newline character from the input string
        cmd[strcspn(cmd, "\n")] = 0;
        
        // Check if user wants to exit
        if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "quit") == 0) {
            break;
        }
        
        // Execute the command
        execute_command(cmd);
    }

    return 0;
}
