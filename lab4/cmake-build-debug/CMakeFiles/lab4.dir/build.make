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
CMAKE_SOURCE_DIR = C:\Users\wansa\OneDrive\Desktop\COP3502C\lab4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\wansa\OneDrive\Desktop\COP3502C\lab4\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lab4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab4.dir/flags.make

CMakeFiles/lab4.dir/main.c.obj: CMakeFiles/lab4.dir/flags.make
CMakeFiles/lab4.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\wansa\OneDrive\Desktop\COP3502C\lab4\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lab4.dir/main.c.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\lab4.dir\main.c.obj   -c C:\Users\wansa\OneDrive\Desktop\COP3502C\lab4\main.c

CMakeFiles/lab4.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab4.dir/main.c.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\wansa\OneDrive\Desktop\COP3502C\lab4\main.c > CMakeFiles\lab4.dir\main.c.i

CMakeFiles/lab4.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab4.dir/main.c.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\wansa\OneDrive\Desktop\COP3502C\lab4\main.c -o CMakeFiles\lab4.dir\main.c.s

# Object files for target lab4
lab4_OBJECTS = \
"CMakeFiles/lab4.dir/main.c.obj"

# External object files for target lab4
lab4_EXTERNAL_OBJECTS =

lab4.exe: CMakeFiles/lab4.dir/main.c.obj
lab4.exe: CMakeFiles/lab4.dir/build.make
lab4.exe: CMakeFiles/lab4.dir/linklibs.rsp
lab4.exe: CMakeFiles/lab4.dir/objects1.rsp
lab4.exe: CMakeFiles/lab4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\wansa\OneDrive\Desktop\COP3502C\lab4\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable lab4.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\lab4.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab4.dir/build: lab4.exe

.PHONY : CMakeFiles/lab4.dir/build

CMakeFiles/lab4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\lab4.dir\cmake_clean.cmake
.PHONY : CMakeFiles/lab4.dir/clean

CMakeFiles/lab4.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\wansa\OneDrive\Desktop\COP3502C\lab4 C:\Users\wansa\OneDrive\Desktop\COP3502C\lab4 C:\Users\wansa\OneDrive\Desktop\COP3502C\lab4\cmake-build-debug C:\Users\wansa\OneDrive\Desktop\COP3502C\lab4\cmake-build-debug C:\Users\wansa\OneDrive\Desktop\COP3502C\lab4\cmake-build-debug\CMakeFiles\lab4.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab4.dir/depend

