# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/CLion-2017.3.2/clion-2017.3.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /usr/local/CLion-2017.3.2/clion-2017.3.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/D2R/Documents/CLionProjects/OS-Lab/D2R's-Shell"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/D2R/Documents/CLionProjects/OS-Lab/D2R's-Shell/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/D2R_s_Shell.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/D2R_s_Shell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/D2R_s_Shell.dir/flags.make

CMakeFiles/D2R_s_Shell.dir/shell.c.o: CMakeFiles/D2R_s_Shell.dir/flags.make
CMakeFiles/D2R_s_Shell.dir/shell.c.o: ../shell.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/D2R/Documents/CLionProjects/OS-Lab/D2R's-Shell/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/D2R_s_Shell.dir/shell.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/D2R_s_Shell.dir/shell.c.o   -c "/home/D2R/Documents/CLionProjects/OS-Lab/D2R's-Shell/shell.c"

CMakeFiles/D2R_s_Shell.dir/shell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/D2R_s_Shell.dir/shell.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/D2R/Documents/CLionProjects/OS-Lab/D2R's-Shell/shell.c" > CMakeFiles/D2R_s_Shell.dir/shell.c.i

CMakeFiles/D2R_s_Shell.dir/shell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/D2R_s_Shell.dir/shell.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/D2R/Documents/CLionProjects/OS-Lab/D2R's-Shell/shell.c" -o CMakeFiles/D2R_s_Shell.dir/shell.c.s

CMakeFiles/D2R_s_Shell.dir/shell.c.o.requires:

.PHONY : CMakeFiles/D2R_s_Shell.dir/shell.c.o.requires

CMakeFiles/D2R_s_Shell.dir/shell.c.o.provides: CMakeFiles/D2R_s_Shell.dir/shell.c.o.requires
	$(MAKE) -f CMakeFiles/D2R_s_Shell.dir/build.make CMakeFiles/D2R_s_Shell.dir/shell.c.o.provides.build
.PHONY : CMakeFiles/D2R_s_Shell.dir/shell.c.o.provides

CMakeFiles/D2R_s_Shell.dir/shell.c.o.provides.build: CMakeFiles/D2R_s_Shell.dir/shell.c.o


# Object files for target D2R_s_Shell
D2R_s_Shell_OBJECTS = \
"CMakeFiles/D2R_s_Shell.dir/shell.c.o"

# External object files for target D2R_s_Shell
D2R_s_Shell_EXTERNAL_OBJECTS =

D2R_s_Shell: CMakeFiles/D2R_s_Shell.dir/shell.c.o
D2R_s_Shell: CMakeFiles/D2R_s_Shell.dir/build.make
D2R_s_Shell: CMakeFiles/D2R_s_Shell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/D2R/Documents/CLionProjects/OS-Lab/D2R's-Shell/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable D2R_s_Shell"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/D2R_s_Shell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/D2R_s_Shell.dir/build: D2R_s_Shell

.PHONY : CMakeFiles/D2R_s_Shell.dir/build

CMakeFiles/D2R_s_Shell.dir/requires: CMakeFiles/D2R_s_Shell.dir/shell.c.o.requires

.PHONY : CMakeFiles/D2R_s_Shell.dir/requires

CMakeFiles/D2R_s_Shell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/D2R_s_Shell.dir/cmake_clean.cmake
.PHONY : CMakeFiles/D2R_s_Shell.dir/clean

CMakeFiles/D2R_s_Shell.dir/depend:
	cd "/home/D2R/Documents/CLionProjects/OS-Lab/D2R's-Shell/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/D2R/Documents/CLionProjects/OS-Lab/D2R's-Shell" "/home/D2R/Documents/CLionProjects/OS-Lab/D2R's-Shell" "/home/D2R/Documents/CLionProjects/OS-Lab/D2R's-Shell/cmake-build-debug" "/home/D2R/Documents/CLionProjects/OS-Lab/D2R's-Shell/cmake-build-debug" "/home/D2R/Documents/CLionProjects/OS-Lab/D2R's-Shell/cmake-build-debug/CMakeFiles/D2R_s_Shell.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/D2R_s_Shell.dir/depend
