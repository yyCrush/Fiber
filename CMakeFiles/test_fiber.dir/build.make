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
CMAKE_SOURCE_DIR = /home/zyy/workspace/myfiber

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zyy/workspace/myfiber

# Include any dependencies generated for this target.
include CMakeFiles/test_fiber.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_fiber.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_fiber.dir/flags.make

CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o: CMakeFiles/test_fiber.dir/flags.make
CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o: tests/test_fiber.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zyy/workspace/myfiber/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o -c /home/zyy/workspace/myfiber/tests/test_fiber.cpp

CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zyy/workspace/myfiber/tests/test_fiber.cpp > CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.i

CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zyy/workspace/myfiber/tests/test_fiber.cpp -o CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.s

CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o.requires:
.PHONY : CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o.requires

CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o.provides: CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o.provides.build
.PHONY : CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o.provides

CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o.provides.build: CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o

# Object files for target test_fiber
test_fiber_OBJECTS = \
"CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o"

# External object files for target test_fiber
test_fiber_EXTERNAL_OBJECTS =

bin/test_fiber: CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o
bin/test_fiber: CMakeFiles/test_fiber.dir/build.make
bin/test_fiber: lib/libmyfiber.so
bin/test_fiber: lib/libmyfiber.so
bin/test_fiber: /usr/local/lib64/libyaml-cpp.a
bin/test_fiber: CMakeFiles/test_fiber.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bin/test_fiber"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_fiber.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_fiber.dir/build: bin/test_fiber
.PHONY : CMakeFiles/test_fiber.dir/build

CMakeFiles/test_fiber.dir/requires: CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o.requires
.PHONY : CMakeFiles/test_fiber.dir/requires

CMakeFiles/test_fiber.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_fiber.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_fiber.dir/clean

CMakeFiles/test_fiber.dir/depend:
	cd /home/zyy/workspace/myfiber && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zyy/workspace/myfiber /home/zyy/workspace/myfiber /home/zyy/workspace/myfiber /home/zyy/workspace/myfiber /home/zyy/workspace/myfiber/CMakeFiles/test_fiber.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_fiber.dir/depend

