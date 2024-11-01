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
