# Ft_nm
Ft_nm is a project undertaken as part of the 42 school curriculum. It's a custom implementation of the UNIX **nm** command, designed to display the symbol table of ELF binaries. This project was developed as part of a UNIX programming assignment and replicates the core functionality of the nm command (GNU nm (GNU Binutils for Ubuntu) 2.40).
By working with ELF binaries, students gain insights into the structure and interpretation of binary files, which are fundamental in systems programming. Implementing features like displaying the symbol table requires a solid understanding of memory management, emphasizing the importance of efficient and error-free memory usage.

**Developed and tested on a Linux Ubuntu 23.04.**

----

## Features
- Compatible with x86_32, x64, object files, and .so files.
- Displays symbols in a format similar to the system's nm command (man nm).
- Robust error handling to prevent unexpected exits like Segmentation faults, bus errors, and double frees.

----

## Build and Installation

Clone the repository:

``git clone https://github.com/jmbertin/Nm/``

Navigate to the project directory and compile using Makefile:

``cd ft_nm``

``make``

The executable ft_nm will be created in the root directory. Use it as described in the Usage section.

----

## Usage

Usage

``./ft_nm [file1] [file2]...``

You can provide multiple files as arguments to ft_nm. If no file is specified, ft_nm will attempt to run on the a.out file if it is present in the current directory.


----

## Contribution
If you encounter any bugs or wish to add features, please feel free to open an issue or submit a pull request.
