# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zyy/workspace/sylar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zyy/workspace/sylar

# Include any dependencies generated for this target.
include CMakeFiles/test_config.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_config.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_config.dir/flags.make

CMakeFiles/test_config.dir/tests/test_config.cpp.o: CMakeFiles/test_config.dir/flags.make
CMakeFiles/test_config.dir/tests/test_config.cpp.o: tests/test_config.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zyy/workspace/sylar/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test_config.dir/tests/test_config.cpp.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_config.dir/tests/test_config.cpp.o -c /home/zyy/workspace/sylar/tests/test_config.cpp

CMakeFiles/test_config.dir/tests/test_config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_config.dir/tests/test_config.cpp.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zyy/workspace/sylar/tests/test_config.cpp > CMakeFiles/test_config.dir/tests/test_config.cpp.i

CMakeFiles/test_config.dir/tests/test_config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_config.dir/tests/test_config.cpp.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zyy/workspace/sylar/tests/test_config.cpp -o CMakeFiles/test_config.dir/tests/test_config.cpp.s

CMakeFiles/test_config.dir/tests/test_config.cpp.o.requires:
.PHONY : CMakeFiles/test_config.dir/tests/test_config.cpp.o.requires

CMakeFiles/test_config.dir/tests/test_config.cpp.o.provides: CMakeFiles/test_config.dir/tests/test_config.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cpp.o.provides.build
.PHONY : CMakeFiles/test_config.dir/tests/test_config.cpp.o.provides

CMakeFiles/test_config.dir/tests/test_config.cpp.o.provides.build: CMakeFiles/test_config.dir/tests/test_config.cpp.o

# Object files for target test_config
test_config_OBJECTS = \
"CMakeFiles/test_config.dir/tests/test_config.cpp.o"

# External object files for target test_config
test_config_EXTERNAL_OBJECTS =

bin/test_config: CMakeFiles/test_config.dir/tests/test_config.cpp.o
bin/test_config: CMakeFiles/test_config.dir/build.make
bin/test_config: lib/libsylar.so
bin/test_config: lib/libsylar.so
bin/test_config: /usr/local/lib64/libyaml-cpp.a
bin/test_config: CMakeFiles/test_config.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bin/test_config"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_config.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_config.dir/build: bin/test_config
.PHONY : CMakeFiles/test_config.dir/build

CMakeFiles/test_config.dir/requires: CMakeFiles/test_config.dir/tests/test_config.cpp.o.requires
.PHONY : CMakeFiles/test_config.dir/requires

CMakeFiles/test_config.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_config.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_config.dir/clean

CMakeFiles/test_config.dir/depend:
	cd /home/zyy/workspace/sylar && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zyy/workspace/sylar /home/zyy/workspace/sylar /home/zyy/workspace/sylar /home/zyy/workspace/sylar /home/zyy/workspace/sylar/CMakeFiles/test_config.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_config.dir/depend

