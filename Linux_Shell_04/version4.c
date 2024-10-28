#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 100

void sigchld_handler(int signo) {
    // Reap all dead processes to avoid zombies
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    pid_t pid;
    int background;

    // Set up signal handler for SIGCHLD
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);

    while (1) {
        printf("PUCITshell@%s:- ", getcwd(NULL, 0));
        fflush(stdout);

        // Read command
        if (!fgets(cmd, MAX_CMD_LEN, stdin)) {
            break; // Exit on EOF
        }

        // Remove trailing newline
        cmd[strcspn(cmd, "\n")] = 0;

        // Check for background execution
        background = 0;
        if (cmd[strlen(cmd) - 1] == '&') {
            background = 1;
            cmd[strlen(cmd) - 1] = 0; // Remove '&'
        }

        // Tokenize the command
        char *token = strtok(cmd, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Null-terminate the argument list

        // Fork a child process
        pid = fork();
        if (pid == 0) {
            // Child process
            if (execvp(args[0], args) == -1) {
                perror("Error executing command");
            }
            exit(EXIT_FAILURE); // Exit if exec fails
        } else if (pid < 0) {
            perror("Fork failed");
        } else {
            // Parent process
            if (!background) {
                // Wait for foreground process to finish
                waitpid(pid, NULL, 0);
            } else {
                // Print background job info
                printf("[%d] %d\n", i, pid);
            }
        }
    }

    return 0;
}