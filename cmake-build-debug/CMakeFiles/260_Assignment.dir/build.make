# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/itworsley/Documents/clion-2018.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/itworsley/Documents/clion-2018.2.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/itworsley/Desktop/260_Assignment

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/itworsley/Desktop/260_Assignment/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/260_Assignment.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/260_Assignment.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/260_Assignment.dir/flags.make

CMakeFiles/260_Assignment.dir/game.c.o: CMakeFiles/260_Assignment.dir/flags.make
CMakeFiles/260_Assignment.dir/game.c.o: ../game.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/itworsley/Desktop/260_Assignment/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/260_Assignment.dir/game.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/260_Assignment.dir/game.c.o   -c /home/itworsley/Desktop/260_Assignment/game.c

CMakeFiles/260_Assignment.dir/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/260_Assignment.dir/game.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/itworsley/Desktop/260_Assignment/game.c > CMakeFiles/260_Assignment.dir/game.c.i

CMakeFiles/260_Assignment.dir/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/260_Assignment.dir/game.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/itworsley/Desktop/260_Assignment/game.c -o CMakeFiles/260_Assignment.dir/game.c.s

# Object files for target 260_Assignment
260_Assignment_OBJECTS = \
"CMakeFiles/260_Assignment.dir/game.c.o"

# External object files for target 260_Assignment
260_Assignment_EXTERNAL_OBJECTS =

260_Assignment: CMakeFiles/260_Assignment.dir/game.c.o
260_Assignment: CMakeFiles/260_Assignment.dir/build.make
260_Assignment: CMakeFiles/260_Assignment.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/itworsley/Desktop/260_Assignment/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 260_Assignment"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/260_Assignment.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/260_Assignment.dir/build: 260_Assignment

.PHONY : CMakeFiles/260_Assignment.dir/build

CMakeFiles/260_Assignment.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/260_Assignment.dir/cmake_clean.cmake
.PHONY : CMakeFiles/260_Assignment.dir/clean

CMakeFiles/260_Assignment.dir/depend:
	cd /home/itworsley/Desktop/260_Assignment/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/itworsley/Desktop/260_Assignment /home/itworsley/Desktop/260_Assignment /home/itworsley/Desktop/260_Assignment/cmake-build-debug /home/itworsley/Desktop/260_Assignment/cmake-build-debug /home/itworsley/Desktop/260_Assignment/cmake-build-debug/CMakeFiles/260_Assignment.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/260_Assignment.dir/depend

