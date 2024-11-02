#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARS 100  
struct var {
    char *str;   
    int global;  // 1 for environment variable, 0 for local variable
};

// Global variable array
struct var variables[MAX_VARS];
int var_count = 0;  

void set_variable(const char *name, const char *value, int is_global) {
    char *var_string = malloc(strlen(name) + strlen(value) + 2); // Allocate space for name=value string
    sprintf(var_string, "%s=%s", name, value); // Create name=value string

    // Check if the variable already exists
    for (int i = 0; i < var_count; i++) {
        if (strncmp(variables[i].str, name, strlen(name)) == 0) {
            // Variable exists, update it
            free(variables[i].str); // Free the old string
            variables[i].str = var_string; // Update with the new string
            variables[i].global = is_global; // Update global flag
            return;
        }
    }

    // If not found, add new variable
    if (var_count < MAX_VARS) {
        variables[var_count].str = var_string;
        variables[var_count].global = is_global;
        var_count++;
    } else {
        printf("Error: Maximum number of variables reached.\n");
    }
}
