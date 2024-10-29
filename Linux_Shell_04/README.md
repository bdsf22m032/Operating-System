# Command History Feature in C

## Project Status
This project implements a command history feature in C using the `readline` library. The program allows users to enter commands, repeat previous commands using a history index, and exit the program. The code is functional and has been tested on Kali Linux.

### Current Bugs
- **Command Execution**: The command execution feature is currently commented out. Uncommenting the `system(command)` line will allow commands to be executed, but caution is advised as it may lead to security vulnerabilities if untrusted input is processed.
- **Input Buffer Size**: The input buffer size is fixed at 256 characters. If a command exceeds this length, it will be truncated, which may lead to unexpected behavior.

## Features Implemented
- **Command Input**: Users can input commands through the terminal.
- **Command History**: The last 10 commands are stored and can be accessed using `!n` where `n` is the command index.
- **Repeat Last Command**: Users can repeat the last command by typing `!-1`.
- **Exit Command**: The program can be exited by typing `exit`.
- **History Limitation**: The history is limited to the last 10 commands using the `stifle_history` function from the `readline` library.
- **Error Handling**: Basic error handling for invalid command formats and out-of-bounds history indices.

### Additional Features
- **Command Listing**: A function to print the last 10 commands in history (not currently called in the main loop but can be implemented).
- **User -Friendly Prompts**: Clear prompts for user input and feedback on command execution.

## Acknowledgments
- **Readline Library**: This project utilizes the `readline` library for handling command input and history management. Documentation can be found at [GNU Readline](https://tiswww.case.edu/php/chet/readline/rltop.html).
- **Stack Overflow**: Various solutions and examples were referenced from Stack Overflow to implement command history and error handling.
- **C Programming Resources**: General C programming concepts were referenced from various online tutorials and documentation.

## Installation Instructions
1. Ensure you have the `readline` library installed:
   ```bash
   sudo apt-get install libreadline-dev