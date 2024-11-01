# MyShell README

## Code Status
The current version of MyShell is functional and capable of executing basic commands, changing directories, and managing background jobs. The following features have been implemented, and extensive testing has been performed to ensure stability.

### Known Bugs
- **Job Management**: The shell does not properly handle cases where a background job exits before the user attempts to kill it, which may lead to an invalid job index.
- **Signal Handling**: Currently, the shell does not handle signals like SIGINT (Ctrl+C) gracefully, which may cause it to terminate unexpectedly.

## Features Implemented
- **Command Prompt**: A simple command prompt that accepts user input.
- **Change Directory**: The ability to change the current working directory using the `cd <path>` command.
- **List Background Jobs**: A `jobs` command that lists all background jobs with their process IDs and commands.
- **Kill Background Jobs**: A `kill <job_index>` command that allows users to terminate a background job by its index.
- **Help Command**: A `help` command that lists all available built-in commands.
- **Execution of External Commands**: The shell can execute external commands by forking a new process and using `execvp`.
- **Background Job Management**: Supports managing multiple background jobs (up to a limit) while keeping track of their PIDs.

### Additional Features
- **Signal Handling (Partially Implemented)**: Basic signal handling has been incorporated, though it requires improvement for robustness.
- **Dynamic Command Execution**: The shell dynamically recognizes and executes both built-in and external commands.

## Acknowledgments
- Special thanks to online resources such as Stack Overflow and the GNU C Library documentation for assistance with C programming and system calls.
- Acknowledgment to classmates and peers for code reviews and suggestions during development.

## Future Improvements
- Implement complete signal handling to manage user interrupts (SIGINT) and other signals.
- Improve job management to handle job termination properly and prevent invalid job references.
- Expand the feature set with additional built-in commands for better usability.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
