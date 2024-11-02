#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARS 100  
// Define the structure for variables
struct var {
    char *str;   
    int global; 
};

// Global variable array
struct var variables[MAX_VARS];
int var_count = 0;  

// Function to add or update a variable
void set_variable(const char *name, const char *value, int is_global) {
    char *var_string = malloc(strlen(name) + strlen(value) + 2); /
    if (!var_string) {
        printf("Memory allocation error\n");
        return;
    }
    sprintf(var_string, "%s=%s", name, value); 
    // Check if the variable already exists
    for (int i = 0; i < var_count; i++) {
        if (strncmp(variables[i].str, name, strlen(name)) == 0 && variables[i].str[strlen(name)] == '=') {
          
            free(variables[i].str); 
            variables[i].str = var_string;
            variables[i].global = is_global; 
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
        free(var_string); 
    }
}

// Function to retrieve a variable
const char *get_variable(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strncmp(variables[i].str, name, strlen(name)) == 0 && variables[i].str[strlen(name)] == '=') {
            return strchr(variables[i].str, '=') + 1; 
        }
    }
    return NULL; 
}

// Function to list all variables
void list_variables() {
    for (int i = 0; i < var_count; i++) {
        printf("%s (%s)\n", variables[i].str, variables[i].global ? "global" : "local");
    }
}

int main() {
    // Set some environment variables
    set_variable("PATH", "/usr/bin", 1);
    set_variable("HOME", "/home/user", 1);

    // Set some local variables
    set_variable("local_var", "value1", 0);
    set_variable("another_var", "value2", 0);

    // List all variables
    printf("All Variables:\n");
    list_variables();

    // Retrieve a variable
    const char *value = get_variable("PATH");
    if (value) {
        printf("Value of PATH: %s\n", value);
    } else {
        printf("PATH not found.\n");
    }

    return 0;
}
