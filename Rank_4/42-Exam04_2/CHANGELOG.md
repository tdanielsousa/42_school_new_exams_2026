# Changelog

All notable changes to the 42 Exam 04 project will be documented in this file.

## [1.1.0] - 2024-01-01

### Updated
- **README.md**: Updated to reflect actual project structure with bin directory and pre-compiled executables
- **PROJECT_STRUCTURE.md**: Comprehensive update with current project status, file counts, and build system changes
- **CHANGELOG.md**: Updated to reflect current project state

### Removed
- **build.sh**: Removed as requested - no longer needed
- **Master Makefile**: Removed as requested - individual compilation preferred
- **Empty Makefiles**: Cleaned up unused empty Makefiles

### Current Project Status
- **Level 1**: All 5 projects ✅ Complete and working
- **Level 2**: 1/3 projects ✅ Complete, 2/3 ⚠️ Need main functions
- **Level 3**: All 2 projects ✅ Complete and working
- **Pre-compiled executables**: Available in `bin/` directory

## [1.0.0] - 2024-01-01

### Added
- **Comprehensive README.md** with project description, structure, and usage instructions
- **Project structure documentation** (`PROJECT_STRUCTURE.md`) with detailed explanations
- **Gitignore file** for C projects to exclude build artifacts and temporary files
- **Improved code quality** with better formatting, comments, and error handling

### Improved
- **n_queens.c**: Enhanced with proper 42 header, better formatting, comprehensive comments, and improved error handling
- **Code organization**: Better file structure and documentation
- **Documentation**: Comprehensive project documentation and usage examples

### Technical Improvements
- **Error handling**: Added proper input validation and error messages
- **Memory management**: Improved memory allocation and cleanup
- **Code standards**: Follow 42 coding standards with proper indentation and naming
- **Testing framework**: Basic testing infrastructure for projects

### Documentation
- **README.md**: Complete project overview with usage examples
- **PROJECT_STRUCTURE.md**: Detailed technical documentation
- **Code comments**: Comprehensive function documentation
- **Usage examples**: Clear examples for each project

## Project Overview

### ✅ Working Projects (8/10)
1. **n_queens** - N-Queens puzzle solver
2. **permutation** - Permutation generator  
3. **power_set** - Power set calculator
4. **rip** - RIP implementation
5. **tsp** - TSP solver
6. **ft_popen** - Custom popen implementation
7. **argo** - Argo interpreter
8. **vbc** - VBC compiler

### ⚠️ Projects Needing Main Functions (2/10)
1. **picoshell** - Main function commented out
2. **sandbox** - Missing main function

### File Structure
- **Source files**: 10 `.c` files across all levels
- **Subject files**: 10 `subject.txt` files with problem descriptions
- **Helper files**: 3 `given.c` files for complex projects
- **Executables**: 8 working executables in `bin/` directory

## Future Enhancements

### Planned Features
- [ ] Complete picoshell implementation (uncomment main function)
- [ ] Complete sandbox implementation (add main function)
- [ ] Comprehensive test suite for all projects
- [ ] Performance benchmarking tools
- [ ] Code coverage analysis

### Code Quality Goals
- [ ] Full 42 coding standards compliance
- [ ] Comprehensive error handling
- [ ] Memory leak prevention
- [ ] Performance optimization
- [ ] Security considerations for system programming projects

### Documentation Goals
- [ ] API documentation for each project
- [ ] Algorithm explanations and complexity analysis
- [ ] System programming concepts documentation
- [ ] Troubleshooting guides
- [ ] Performance tuning guides

---

## Version History

- **1.1.0**: Updated documentation and project structure, removed build system
- **1.0.0**: Initial improved version with comprehensive documentation
- **0.1.0**: Original exam submission

## Contributing

This is a personal project for 42 Exam 04. The improvements serve as:
- Learning material for algorithmic concepts
- Reference for system programming techniques
- Example of proper C programming practices
- Demonstration of build system organization

## License

This project is for educational purposes as part of the 42 curriculum. 