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