# Shell-03 (PUCITshell)

This is a simple shell implementation in C, designed to run on Linux systems. The shell supports executing external commands, both in the foreground and background, while handling signals to avoid zombie processes.

## Code Status

- **Current Status**: The shell is fully functional for executing commands and managing background processes.
- **Bugs Found**: 
  - The `cd` command is not implemented, which limits directory navigation.
  - Background processes do not display their exit status upon completion.
  - The shell does not currently support input redirection or piping.

## Features

- Execute external commands.
- Background execution using `&`.
- Signal handling to prevent zombie processes.
- Basic command parsing and tokenization.
- **Additional Features**:
  - Error handling for invalid commands.
  - Display of background job information (process ID).
  - Support for command termination using Ctrl+C.

## Acknowledgments

- Special thanks to the following resources:
  - [GeeksforGeeks](https://www.geeksforgeeks.org) for tutorials on process management and signal handling in C.
  - [The Linux Programming Interface](http://man7.org/tlpi/) by Michael Kerrisk for in-depth knowledge of Linux system calls.
  - My peers and instructors for their guidance and support during the development of this project.

