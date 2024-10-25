#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 100

void execute_command(char *cmd) {
    char *args[MAX_ARGS];
    char *args_pipe[MAX_ARGS];
    char *input_file = NULL;
    char *output_file = NULL;
    int pipe_fd[2];
    int has_pipe = 0;

    // Tokenize the command for input/output redirection and pipe
    char *token = strtok(cmd, " ");
    int i = 0;

    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            input_file = strtok(NULL, " ");
        } else if (strcmp(token, ">") == 0) {
            output_file = strtok(NULL, " ");
        } else if (strcmp(token, "|") == 0) {
            has_pipe = 1;
            token = strtok(NULL, " ");
            int j = 0;
            while (token != NULL) {
                args_pipe[j++] = token;
                token = strtok(NULL, " ");
            }
            args_pipe[j] = NULL;
            break;
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (has_pipe) {
        // Create a pipe
        pipe(pipe_fd);
        pid_t pid1 = fork();

        if (pid1 == 0) {
            // First child process for the command before the pipe
            if (input_file) {
                int in_fd = open(input_file, O_RDONLY);
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            execvp(args[0], args);
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL);
            close(pipe_fd[1]);

            // Second child process for the command after the pipe
            pid_t pid2 = fork();
            if (pid2 == 0) {
                dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe
                close(pipe_fd[0]);
                if (output_file) {
                    int out_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(out_fd, STDOUT_FILENO);
                    close(out_fd);
                }
                execvp(args_pipe[0], args_pipe);
                perror("execvp failed");
                exit(EXIT_FAILURE);
            } else {
                close(pipe_fd[0]);
                wait(NULL);
            }
        }
    } else {
        // No pipe, just execute the command with redirection if needed
        pid_t pid = fork();
        if (pid == 0) {
            if (input_file) {
                int in_fd = open(input_file, O_RDONLY);
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            if (output_file) {
                int out_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(out_fd, STDOUT_FILENO);
                close(out_fd);
            }
            execvp(args[0], args);
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }
    }
}

int main() {
    char cmd[MAX_CMD_LEN];

    while (1) {
        printf("PUCITshell@/home/arif/:- ");
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            break; // Exit on EOF
        }
        cmd[strcspn(cmd, "\n")] = 0; // Remove newline character
        if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "quit") == 0) {
            break;
        }
        execute_command(cmd);
    }

    return 0;
}
