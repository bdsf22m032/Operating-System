#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define HISTORY_FILE ".simple_shell_history"
#define MAX_HISTORY_SIZE 10

// Function to save history to file
void save_history() {
    FILE *file = fopen(HISTORY_FILE, "w");
    if (!file) {
        perror("fopen");
        return;
    }
    HIST_ENTRY **the_history_list = history_list();
    if (the_history_list) {
        for (int i = 0; the_history_list[i]; i++) {
            fprintf(file, "%s\n", the_history_list[i]->line);
        }
    }
    fclose(file);
}

// Function to load history from file
void load_history() {
    FILE *file = fopen(HISTORY_FILE, "r");
    if (!file) return;
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1) {
        line[strcspn(line, "\n")] = 0;  // Remove newline
        add_history(line);
    }
    free(line);
    fclose(file);
}

// Function to get the nth command from history
char *get_history_command(int index) {
    HIST_ENTRY **the_history_list = history_list();
    int history_count = history_length;
    if (index < 0) {
        index = history_count + index;
    } else {
        index -= 1;
    }
    return (index >= 0 && index < history_count) ? the_history_list[index]->line : NULL;
}

int main() {
    // Load history from file
    using_history();
    load_history();

    char *input;
    while ((input = readline("shell> ")) != NULL) {
        if (strlen(input) > 0) {
            add_history(input);  // Add to history
            if (history_length > MAX_HISTORY_SIZE) {
                remove_history(0);  // Remove oldest command
            }
        }

        // Check for "!" command for history recall
        if (input[0] == '!') {
            int command_number;
            if (sscanf(input + 1, "%d", &command_number) == 1) {
                char *command = get_history_command(command_number);
                if (command) {
                    printf("Repeating command: %s\n", command);
                    system(command);
                } else {
                    printf("No such command in history.\n");
                }
            } else {
                printf("Invalid command syntax.\n");
            }
        } else if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        } else {
            // Execute the entered command
            system(input);
        }

        free(input);
    }

    // Save history and cleanup
    save_history();
    clear_history();
    return 0;
}
