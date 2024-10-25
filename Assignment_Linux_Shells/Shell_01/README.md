# MyShell

## Code Status

- **Current Version**: 1.0.0
- **Status**: Stable
- **Bugs Found**:
  - Occasionally, the shell may not handle certain edge cases with input redirection properly, leading to unexpected behavior.
  - The `cd` command does not support relative paths correctly in some scenarios.
  - Error messages for unsupported commands could be more descriptive.

## Features Implemented

- **Basic Command Execution**: Execute standard shell commands such as `ls`, `cat`, `echo`, and `pwd`.
- **Input/Output Redirection**: Redirect output to files using `>` and read input from files using `<`.
- **Piping**: Connect multiple commands using pipes (`|`).
- **Change Directory**: Navigate between directories using the `cd` command.
- **Clear Screen**: Clear the terminal screen with the `clear` command.
- **Environment Variable Access**: Use environment variables in commands (e.g., `$HOME`).
- **Custom Error Handling**: Informative error messages for invalid commands and file operations.

### Additional Features

- **Command History**: Users can view and reuse previous commands by pressing the up and down arrow keys.
- **Tab Completion**: Basic tab completion for file names and commands.
- **Support for Background Processes**: Run commands in the background using `&`.

.