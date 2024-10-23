# PUCIT Shell Version 01
## Description
PUCIT Shell is a simple command-line shell program developed for educational purposes. It serves as an interface for users to execute system commands and manage processes in a Unix-like environment. The shell supports basic functionalities, allowing users to interact with the operating system through command input.

## Features
### Custom Prompt:
              Displays a user-friendly prompt (PUCITshell:-) which can be customized to include additional information such as the machine name, username, or current working directory using getcwd().

### Command Execution:
              Accepts a single line of input from the user, which can include commands, options, and arguments. The shell parses this input into tokens, forks a child process, and executes the command using the exec family of functions.

### Process Management: 
              The parent process waits for the child process to complete before displaying the prompt again, ensuring orderly command execution.

### Exit Functionality: 
               Users can exit the shell program gracefully by pressing <CTRL+D>, which terminates the shell session