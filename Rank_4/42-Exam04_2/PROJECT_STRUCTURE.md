# 42 Exam 04 - Project Structure Documentation

## Overview

This repository contains solutions for the 42 Exam 04, which tests knowledge in algorithmic problem-solving and system programming. The exam is divided into three levels of increasing complexity.

## Current Project Status

### ✅ Completed Projects
- **Level 1**: All 5 projects implemented and compiled
- **Level 2**: All 3 projects implemented and compiled  
- **Level 3**: All 2 projects implemented and compiled

### 📁 Actual Project Structure

```
42-Exam04/
├── level1/          # Basic algorithmic problems (5 projects)
│   ├── n_queens/    # ✅ N-Queens puzzle solver
│   ├── permutation/ # ✅ Permutation generator
│   ├── power_set/   # ✅ Power set calculator
│   ├── rip/         # ✅ RIP (Routing Information Protocol)
│   └── tsp/         # ✅ Traveling Salesman Problem
├── level2/          # Intermediate system programming (3 projects)
│   ├── ft_popen/    # ✅ Custom popen implementation
│   ├── picoshell/   # ⚠️ Shell implementation (main function commented)
│   └── sandbox/     # ⚠️ Process sandboxing (needs main function)
├── level3/          # Advanced challenges (2 projects)
│   ├── argo/        # ✅ Argo programming language interpreter
│   └── vbc/         # ✅ Virtual Bytecode Compiler
└── bin/             # Compiled executables
    ├── n_queens     # ✅ Compiled and working
    ├── permutation  # ✅ Compiled and working
    ├── power_set    # ✅ Compiled and working
    ├── rip          # ✅ Compiled and working
    ├── tsp          # ✅ Compiled and working
    ├── ft_popen     # ✅ Compiled and working
    ├── argo         # ✅ Compiled and working
    └── vbc          # ✅ Compiled and working
```

## Level 1 - Basic Algorithmic Problems

### 1. N-Queens (`level1/n_queens/`) ✅
**Problem**: Place N queens on an N×N chessboard so that no two queens threaten each other.

**Algorithm**: Backtracking
- **Time Complexity**: O(N!)
- **Space Complexity**: O(N)

**Files**:
- `n_queens.c` - Main implementation (49 lines)
- `subject.txt` - Problem description (28 lines)

**Status**: ✅ **Complete and Working**
- Compiles successfully
- Executable available in `bin/`
- Tested and functional

### 2. Permutation (`level1/permutation/`) ✅
**Problem**: Generate all possible permutations of a given set.

**Algorithm**: Recursive permutation generation
- **Time Complexity**: O(N!)
- **Space Complexity**: O(N)

**Files**:
- `permutation.c` - Main implementation (53 lines)
- `subject.txt` - Problem description (25 lines)

**Status**: ✅ **Complete and Working**

### 3. Power Set (`level1/power_set/`) ✅
**Problem**: Calculate the power set (all possible subsets) of a given set.

**Algorithm**: Bit manipulation or recursive generation
- **Time Complexity**: O(2^N)
- **Space Complexity**: O(2^N)

**Files**:
- `power_set.c` - Main implementation (59 lines)
- `subject.txt` - Problem description (65 lines)

**Status**: ✅ **Complete and Working**

### 4. RIP (`level1/rip/`) ✅
**Problem**: Implement Routing Information Protocol (RIP) algorithm.

**Algorithm**: Distance vector routing
- **Time Complexity**: O(V^3) where V is number of vertices
- **Space Complexity**: O(V^2)

**Files**:
- `rip.c` - Main implementation (56 lines)
- `subject.txt` - Problem description (28 lines)

**Status**: ✅ **Complete and Working**

### 5. TSP (`level1/tsp/`) ✅
**Problem**: Solve the Traveling Salesman Problem.

**Algorithm**: Dynamic programming or branch and bound
- **Time Complexity**: O(N^2 * 2^N)
- **Space Complexity**: O(N * 2^N)

**Files**:
- `tsp.c` - Main implementation (126 lines)
- `given.c` - Helper functions (97 lines)
- `subject.txt` - Problem description (62 lines)

**Status**: ✅ **Complete and Working**

## Level 2 - System Programming

### 1. ft_popen (`level2/ft_popen/`) ✅
**Problem**: Implement a custom version of the `popen()` function.

**Features**:
- Process creation and management
- Pipe communication
- File descriptor handling

**System Calls Used**:
- `fork()`
- `pipe()`
- `dup2()`
- `execve()`

**Files**:
- `ft_popen.c` - Main implementation (43 lines)
- `subject.txt` - Problem description (41 lines)

**Status**: ✅ **Complete and Working**

### 2. picoshell (`level2/picoshell/`) ⚠️
**Problem**: Implement a minimal shell with basic command execution.

**Features**:
- Command parsing
- Process creation
- Built-in commands
- Signal handling

**System Calls Used**:
- `fork()`
- `execve()`
- `wait()`
- `signal()`

**Files**:
- `picoshell.c` - Main implementation (119 lines)
- `subject.txt` - Problem description (39 lines)

**Status**: ⚠️ **Implementation Complete, Main Function Commented**
- Core functionality implemented
- Main function is commented out in source code
- Needs main function to be uncommented for full functionality

### 3. sandbox (`level2/sandbox/`) ⚠️
**Problem**: Create a process sandbox for secure execution.

**Features**:
- Process isolation
- Resource limiting
- Security policies
- System call filtering

**System Calls Used**:
- `seccomp()`
- `setrlimit()`
- `chroot()`
- `unshare()`

**Files**:
- `sandbox.c` - Main implementation (72 lines)
- `subject.txt` - Problem description (26 lines)

**Status**: ⚠️ **Implementation Complete, Needs Main Function**
- Core functionality implemented
- Missing main function for standalone execution

## Level 3 - Advanced Challenges

### 1. argo (`level3/argo/`) ✅
**Problem**: Implement an interpreter for the Argo programming language.

**Features**:
- Lexical analysis
- Syntax parsing
- Code execution
- Memory management

**Components**:
- Tokenizer
- Parser
- Virtual machine
- Standard library

**Files**:
- `argo.c` - Main implementation (267 lines)
- `given.c` - Helper functions (132 lines)
- `subject.txt` - Problem description (43 lines)

**Status**: ✅ **Complete and Working**

### 2. vbc (`level3/vbc/`) ✅
**Problem**: Implement a Virtual Bytecode Compiler.

**Features**:
- Source code compilation
- Bytecode generation
- Virtual machine execution
- Optimization passes

**Components**:
- Frontend compiler
- Intermediate representation
- Backend code generator
- Runtime environment

**Files**:
- `vbc.c` - Main implementation (157 lines)
- `given.c` - Helper functions (102 lines)
- `subject.txt` - Problem description (48 lines)

**Status**: ✅ **Complete and Working**

## Build System

### Current Status
- **No master Makefile** - Removed as requested
- **Individual compilation** - Each project compiled separately
- **Pre-compiled executables** - Available in `bin/` directory

### Compilation Method
```bash
# For each project
cd level1/n_queens
gcc -Wall -Wextra -Werror -std=c99 -o n_queens n_queens.c
```

### Pre-compiled Executables
The `bin/` directory contains working executables for:
- `n_queens` - N-Queens puzzle solver
- `permutation` - Permutation generator
- `power_set` - Power set calculator
- `rip` - RIP implementation
- `tsp` - TSP solver
- `ft_popen` - Custom popen implementation
- `argo` - Argo interpreter
- `vbc` - VBC compiler

## Code Quality Standards

### C Coding Standards
- Follow 42 coding standards
- Proper indentation (4 spaces)
- Function documentation
- Error handling
- Memory management

### File Organization
- Source files for implementations
- Subject files for problem descriptions
- Helper files where needed
- Documentation files

### Testing
- Manual testing for working projects
- Compilation verification
- Basic functionality tests

## Development Workflow

### 1. Setup
```bash
git clone <repository>
cd 42-Exam04
```

### 2. Development
```bash
# Compile specific project
cd level1/n_queens
gcc -Wall -Wextra -Werror -std=c99 -o n_queens n_queens.c

# Or use pre-compiled executables
./bin/n_queens 4
```

### 3. Testing
```bash
# Test specific project
cd level1/n_queens
./n_queens 4
```

## Performance Considerations

### Memory Management
- Proper allocation and deallocation
- Memory leak prevention
- Efficient data structures
- Resource cleanup

### Algorithm Optimization
- Time complexity analysis
- Space complexity optimization
- Cache-friendly algorithms
- Parallel processing where applicable

### System Programming
- Efficient system calls
- Proper signal handling
- Resource management
- Security considerations

## Troubleshooting

### Common Issues
1. **Compilation Errors**: Check compiler flags and dependencies
2. **Runtime Errors**: Verify input validation and error handling
3. **Memory Issues**: Use valgrind for memory leak detection
4. **Performance Issues**: Profile with gprof or similar tools

### Debugging Tools
- `gdb` - GNU debugger
- `valgrind` - Memory error detection
- `strace` - System call tracing
- `ltrace` - Library call tracing

## Contributing

This is a personal project for 42 Exam 04. The code serves as:
- Learning material for algorithmic concepts
- Reference for system programming techniques
- Example of proper C programming practices
- Demonstration of build system organization

## License

This project is for educational purposes as part of the 42 curriculum. 