#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_JOBS 100          
#define MAX_CMD_LENGTH 1024   

// Function to change the current working directory
void change_directory(char *path) {
    if (chdir(path) != 0) {
        perror("cd failed");  
    }
}

// Function to print help for built-in commands
void help_commands() {
    printf("Available built-in commands:\n");
    printf("cd <path> - Change the current directory to <path>\n");
    printf("exit - Exit the shell\n");
    printf("jobs - List background jobs\n");
    printf("kill <job_index> - Kill the job at <job_index>\n");
    printf("help - List available commands\n");
}

int main() {
    char command[MAX_CMD_LENGTH]; // Buffer for user input
    char *args[100]; // Array to store command arguments

    while (1) {
        printf("myshell> "); // Print shell prompt
        // Get user input
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break; // Exit on EOF
        }

        // Remove newline character
        command[strcspn(command, "\n")] = 0;

        // Tokenize the command input into arguments
        int i = 0;
        char *token = strtok(command, " ");
        while (token != NULL) {
            args[i++] = token; // Add each token to args array
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Null-terminate the array

        // If there is a command, execute it
        if (i > 0) {
            execute_command(args);
        }
    }

    return 0; // Return success
}
// Structure to hold job information (PID and command)
typedef struct {
    pid_t pid;                
    char command[MAX_CMD_LENGTH]; 
} Job;

Job jobs[MAX_JOBS];          // Array to store active jobs
int job_count = 0; // Initialize job count

// Function to list all background jobs
void list_jobs() {
    if (job_count == 0) {
        printf("No background jobs.\n"); // No jobs to display
    } else {
        for (int i = 0; i < job_count; i++) {
            printf("[%d] PID: %d Command: %s\n", i, jobs[i].pid, jobs[i].command);
        }
    }
}

// Function to kill a background job given its index
void kill_job(int job_index) {
    if (job_index < 0 || job_index >= job_count) {
        printf("No such job.\n"); // Check if index is valid
        return;
    }
    if (kill(jobs[job_index].pid, SIGKILL) == 0) {
        printf("Killed job %s with PID %d\n", jobs[job_index].command, jobs[job_index].pid);
        // Remove job from the list
        for (int i = job_index; i < job_count - 1; i++) {
            jobs[i] = jobs[i + 1]; // Shift jobs to fill the gap
        }
        job_count--; // Decrease job count
    } else {
        perror("kill failed"); // Print error if killing the job fails
    }
}

// (Main function code from Part 2 goes here)
// Function to execute a command
void execute_command(char **command) {
    if (strcmp(command[0], "cd") == 0) {
        change_directory(command[1] ? command[1] : getenv("HOME")); // Change to specified directory or HOME
    } else if (strcmp(command[0], "exit") == 0) {
        exit(0); // Exit the shell
    } else if (strcmp(command[0], "jobs") == 0) {
        list_jobs(); // List background jobs
    } else if (strcmp(command[0], "kill") == 0) {
        if (command[1]) {
            kill_job(atoi(command[1])); // Convert string index to integer
        } else {
            printf("Usage: kill <job_index>\n"); // Print usage message
        }
    } else if (strcmp(command[0], "help") == 0) {
        help_commands(); // Show help for commands
    } else {
        // Execute external commands
        pid_t pid = fork(); // Create a new process
        if (pid == 0) {
            // Child process
            execvp(command[0], command); // Replace child process with the command
            perror("exec failed"); // Print error if exec fails
            exit(1); // Exit child process
        } else if (pid > 0) {
            // Parent process
            // Add the new job to the job list if there is space
            if (job_count < MAX_JOBS) {
                strcpy(jobs[job_count].command, command[0]); // Store command
                jobs[job_count].pid = pid; // Store PID
                job_count++; // Increment job count
            } else {
                printf("Max job limit reached.\n"); // Print message if limit is reached
            }
            waitpid(pid, NULL, 0); // Wait for the child process to finish
        } else {
            perror("fork failed"); // Print error if fork fails
        }
    }
}

// (Main function code from Part 3 goes here)
