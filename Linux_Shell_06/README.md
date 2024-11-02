# Shell-Version-06

## Code Status
- **Current Status**: The code is functional and implements all required features.
- **Known Bugs**:
  - Issue with the display function where variable values with `=` in them aren't parsed correctly.
  - Minor memory leak when freeing dynamically allocated variables in certain cases.

## Implemented Features
- **Variable Management**:
  - Allows adding, updating, and removing variables.
  - Distinguishes between local (user-defined) and environment variables.
- **Variable Display**:
  - Displays variables with their names, values, and types (local or global).
  - Format: `Name: <name>, Value: <value>, Type: <local/global>`.
- **Additional Features**:
  - Error handling for invalid variable names.
  - Automatic memory cleanup for unused variables.

## Acknowledgments
- Special thanks to [Helper’s Name or Online Resource Link], whose guidance was instrumental in resolving memory management issues.
- Referenced `cplusplus.com` and `geeksforgeeks.org` for syntax and examples on dynamic memory allocation and string manipulation in C.
