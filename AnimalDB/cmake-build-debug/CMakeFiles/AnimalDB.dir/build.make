# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /snap/clion/114/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/114/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vtuchyna/CLionProjects/AnimalDB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vtuchyna/CLionProjects/AnimalDB/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AnimalDB.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AnimalDB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AnimalDB.dir/flags.make

CMakeFiles/AnimalDB.dir/main.cpp.o: CMakeFiles/AnimalDB.dir/flags.make
CMakeFiles/AnimalDB.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vtuchyna/CLionProjects/AnimalDB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AnimalDB.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AnimalDB.dir/main.cpp.o -c /home/vtuchyna/CLionProjects/AnimalDB/main.cpp

CMakeFiles/AnimalDB.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AnimalDB.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vtuchyna/CLionProjects/AnimalDB/main.cpp > CMakeFiles/AnimalDB.dir/main.cpp.i

CMakeFiles/AnimalDB.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AnimalDB.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vtuchyna/CLionProjects/AnimalDB/main.cpp -o CMakeFiles/AnimalDB.dir/main.cpp.s

# Object files for target AnimalDB
AnimalDB_OBJECTS = \
"CMakeFiles/AnimalDB.dir/main.cpp.o"

# External object files for target AnimalDB
AnimalDB_EXTERNAL_OBJECTS =

AnimalDB: CMakeFiles/AnimalDB.dir/main.cpp.o
AnimalDB: CMakeFiles/AnimalDB.dir/build.make
AnimalDB: /usr/lib/x86_64-linux-gnu/libmysqlclient.so
AnimalDB: /usr/lib/x86_64-linux-gnu/libmysqlpp.so
AnimalDB: /usr/local/lib/libcppkafka.so.0.3.1
AnimalDB: /usr/lib/x86_64-linux-gnu/librdkafka.so
AnimalDB: CMakeFiles/AnimalDB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vtuchyna/CLionProjects/AnimalDB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AnimalDB"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AnimalDB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AnimalDB.dir/build: AnimalDB

.PHONY : CMakeFiles/AnimalDB.dir/build

CMakeFiles/AnimalDB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AnimalDB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AnimalDB.dir/clean

CMakeFiles/AnimalDB.dir/depend:
	cd /home/vtuchyna/CLionProjects/AnimalDB/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vtuchyna/CLionProjects/AnimalDB /home/vtuchyna/CLionProjects/AnimalDB /home/vtuchyna/CLionProjects/AnimalDB/cmake-build-debug /home/vtuchyna/CLionProjects/AnimalDB/cmake-build-debug /home/vtuchyna/CLionProjects/AnimalDB/cmake-build-debug/CMakeFiles/AnimalDB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AnimalDB.dir/depend

