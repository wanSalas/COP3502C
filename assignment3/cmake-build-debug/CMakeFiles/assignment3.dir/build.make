# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/assignment3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/assignment3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/assignment3.dir/flags.make

CMakeFiles/assignment3.dir/main.c.obj: CMakeFiles/assignment3.dir/flags.make
CMakeFiles/assignment3.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/assignment3.dir/main.c.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\assignment3.dir\main.c.obj   -c C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3\main.c

CMakeFiles/assignment3.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/assignment3.dir/main.c.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3\main.c > CMakeFiles\assignment3.dir\main.c.i

CMakeFiles/assignment3.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/assignment3.dir/main.c.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3\main.c -o CMakeFiles\assignment3.dir\main.c.s

CMakeFiles/assignment3.dir/leak_detector_c.c.obj: CMakeFiles/assignment3.dir/flags.make
CMakeFiles/assignment3.dir/leak_detector_c.c.obj: ../leak_detector_c.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/assignment3.dir/leak_detector_c.c.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\assignment3.dir\leak_detector_c.c.obj   -c C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3\leak_detector_c.c

CMakeFiles/assignment3.dir/leak_detector_c.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/assignment3.dir/leak_detector_c.c.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3\leak_detector_c.c > CMakeFiles\assignment3.dir\leak_detector_c.c.i

CMakeFiles/assignment3.dir/leak_detector_c.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/assignment3.dir/leak_detector_c.c.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3\leak_detector_c.c -o CMakeFiles\assignment3.dir\leak_detector_c.c.s

# Object files for target assignment3
assignment3_OBJECTS = \
"CMakeFiles/assignment3.dir/main.c.obj" \
"CMakeFiles/assignment3.dir/leak_detector_c.c.obj"

# External object files for target assignment3
assignment3_EXTERNAL_OBJECTS =

assignment3.exe: CMakeFiles/assignment3.dir/main.c.obj
assignment3.exe: CMakeFiles/assignment3.dir/leak_detector_c.c.obj
assignment3.exe: CMakeFiles/assignment3.dir/build.make
assignment3.exe: CMakeFiles/assignment3.dir/linklibs.rsp
assignment3.exe: CMakeFiles/assignment3.dir/objects1.rsp
assignment3.exe: CMakeFiles/assignment3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable assignment3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\assignment3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/assignment3.dir/build: assignment3.exe

.PHONY : CMakeFiles/assignment3.dir/build

CMakeFiles/assignment3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\assignment3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/assignment3.dir/clean

CMakeFiles/assignment3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3 C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3 C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3\cmake-build-debug C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3\cmake-build-debug C:\Users\wansa\OneDrive\Desktop\COP3502C\assignment3\cmake-build-debug\CMakeFiles\assignment3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/assignment3.dir/depend
