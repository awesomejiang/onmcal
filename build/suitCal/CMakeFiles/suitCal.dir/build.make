# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jiawei/Desktop/onmcal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jiawei/Desktop/onmcal/build

# Include any dependencies generated for this target.
include suitCal/CMakeFiles/suitCal.dir/depend.make

# Include the progress variables for this target.
include suitCal/CMakeFiles/suitCal.dir/progress.make

# Include the compile flags for this target's objects.
include suitCal/CMakeFiles/suitCal.dir/flags.make

suitCal/CMakeFiles/suitCal.dir/demo.cpp.o: suitCal/CMakeFiles/suitCal.dir/flags.make
suitCal/CMakeFiles/suitCal.dir/demo.cpp.o: ../suitCal/demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiawei/Desktop/onmcal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object suitCal/CMakeFiles/suitCal.dir/demo.cpp.o"
	cd /home/jiawei/Desktop/onmcal/build/suitCal && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/suitCal.dir/demo.cpp.o -c /home/jiawei/Desktop/onmcal/suitCal/demo.cpp

suitCal/CMakeFiles/suitCal.dir/demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/suitCal.dir/demo.cpp.i"
	cd /home/jiawei/Desktop/onmcal/build/suitCal && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiawei/Desktop/onmcal/suitCal/demo.cpp > CMakeFiles/suitCal.dir/demo.cpp.i

suitCal/CMakeFiles/suitCal.dir/demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/suitCal.dir/demo.cpp.s"
	cd /home/jiawei/Desktop/onmcal/build/suitCal && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiawei/Desktop/onmcal/suitCal/demo.cpp -o CMakeFiles/suitCal.dir/demo.cpp.s

suitCal/CMakeFiles/suitCal.dir/demo.cpp.o.requires:

.PHONY : suitCal/CMakeFiles/suitCal.dir/demo.cpp.o.requires

suitCal/CMakeFiles/suitCal.dir/demo.cpp.o.provides: suitCal/CMakeFiles/suitCal.dir/demo.cpp.o.requires
	$(MAKE) -f suitCal/CMakeFiles/suitCal.dir/build.make suitCal/CMakeFiles/suitCal.dir/demo.cpp.o.provides.build
.PHONY : suitCal/CMakeFiles/suitCal.dir/demo.cpp.o.provides

suitCal/CMakeFiles/suitCal.dir/demo.cpp.o.provides.build: suitCal/CMakeFiles/suitCal.dir/demo.cpp.o


# Object files for target suitCal
suitCal_OBJECTS = \
"CMakeFiles/suitCal.dir/demo.cpp.o"

# External object files for target suitCal
suitCal_EXTERNAL_OBJECTS =

suitCal/suitCal: suitCal/CMakeFiles/suitCal.dir/demo.cpp.o
suitCal/suitCal: suitCal/CMakeFiles/suitCal.dir/build.make
suitCal/suitCal: /usr/local/lib/libmongocxx.so
suitCal/suitCal: /usr/local/lib/libbsoncxx.so
suitCal/suitCal: suitCal/CMakeFiles/suitCal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jiawei/Desktop/onmcal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable suitCal"
	cd /home/jiawei/Desktop/onmcal/build/suitCal && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/suitCal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
suitCal/CMakeFiles/suitCal.dir/build: suitCal/suitCal

.PHONY : suitCal/CMakeFiles/suitCal.dir/build

suitCal/CMakeFiles/suitCal.dir/requires: suitCal/CMakeFiles/suitCal.dir/demo.cpp.o.requires

.PHONY : suitCal/CMakeFiles/suitCal.dir/requires

suitCal/CMakeFiles/suitCal.dir/clean:
	cd /home/jiawei/Desktop/onmcal/build/suitCal && $(CMAKE_COMMAND) -P CMakeFiles/suitCal.dir/cmake_clean.cmake
.PHONY : suitCal/CMakeFiles/suitCal.dir/clean

suitCal/CMakeFiles/suitCal.dir/depend:
	cd /home/jiawei/Desktop/onmcal/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jiawei/Desktop/onmcal /home/jiawei/Desktop/onmcal/suitCal /home/jiawei/Desktop/onmcal/build /home/jiawei/Desktop/onmcal/build/suitCal /home/jiawei/Desktop/onmcal/build/suitCal/CMakeFiles/suitCal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : suitCal/CMakeFiles/suitCal.dir/depend

