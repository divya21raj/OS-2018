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
CMAKE_SOURCE_DIR = /home/D2R/Documents/CLionProjects/OS-Lab/File-Copy-Utility

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/D2R/Documents/CLionProjects/OS-Lab/File-Copy-Utility/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/File_Copy_Utility.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/File_Copy_Utility.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/File_Copy_Utility.dir/flags.make

CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.o: CMakeFiles/File_Copy_Utility.dir/flags.make
CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.o: ../file-copy-utility.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/D2R/Documents/CLionProjects/OS-Lab/File-Copy-Utility/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.o   -c /home/D2R/Documents/CLionProjects/OS-Lab/File-Copy-Utility/file-copy-utility.c

CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/D2R/Documents/CLionProjects/OS-Lab/File-Copy-Utility/file-copy-utility.c > CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.i

CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/D2R/Documents/CLionProjects/OS-Lab/File-Copy-Utility/file-copy-utility.c -o CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.s

CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.o.requires:

.PHONY : CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.o.requires

CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.o.provides: CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.o.requires
	$(MAKE) -f CMakeFiles/File_Copy_Utility.dir/build.make CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.o.provides.build
.PHONY : CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.o.provides

CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.o.provides.build: CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.o


# Object files for target File_Copy_Utility
File_Copy_Utility_OBJECTS = \
"CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.o"

# External object files for target File_Copy_Utility
File_Copy_Utility_EXTERNAL_OBJECTS =

File_Copy_Utility: CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.o
File_Copy_Utility: CMakeFiles/File_Copy_Utility.dir/build.make
File_Copy_Utility: CMakeFiles/File_Copy_Utility.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/D2R/Documents/CLionProjects/OS-Lab/File-Copy-Utility/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable File_Copy_Utility"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/File_Copy_Utility.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/File_Copy_Utility.dir/build: File_Copy_Utility

.PHONY : CMakeFiles/File_Copy_Utility.dir/build

CMakeFiles/File_Copy_Utility.dir/requires: CMakeFiles/File_Copy_Utility.dir/file-copy-utility.c.o.requires

.PHONY : CMakeFiles/File_Copy_Utility.dir/requires

CMakeFiles/File_Copy_Utility.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/File_Copy_Utility.dir/cmake_clean.cmake
.PHONY : CMakeFiles/File_Copy_Utility.dir/clean

CMakeFiles/File_Copy_Utility.dir/depend:
	cd /home/D2R/Documents/CLionProjects/OS-Lab/File-Copy-Utility/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/D2R/Documents/CLionProjects/OS-Lab/File-Copy-Utility /home/D2R/Documents/CLionProjects/OS-Lab/File-Copy-Utility /home/D2R/Documents/CLionProjects/OS-Lab/File-Copy-Utility/cmake-build-debug /home/D2R/Documents/CLionProjects/OS-Lab/File-Copy-Utility/cmake-build-debug /home/D2R/Documents/CLionProjects/OS-Lab/File-Copy-Utility/cmake-build-debug/CMakeFiles/File_Copy_Utility.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/File_Copy_Utility.dir/depend

