# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\fbeze\OneDrive\Documentos\Faculdade\LaboratorioDeProgramacao\Trabalho04

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\fbeze\OneDrive\Documentos\Faculdade\LaboratorioDeProgramacao\Trabalho04\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Trabalho04.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Trabalho04.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Trabalho04.dir/flags.make

CMakeFiles/Trabalho04.dir/main.cpp.obj: CMakeFiles/Trabalho04.dir/flags.make
CMakeFiles/Trabalho04.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\fbeze\OneDrive\Documentos\Faculdade\LaboratorioDeProgramacao\Trabalho04\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Trabalho04.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Trabalho04.dir\main.cpp.obj -c C:\Users\fbeze\OneDrive\Documentos\Faculdade\LaboratorioDeProgramacao\Trabalho04\main.cpp

CMakeFiles/Trabalho04.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Trabalho04.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\fbeze\OneDrive\Documentos\Faculdade\LaboratorioDeProgramacao\Trabalho04\main.cpp > CMakeFiles\Trabalho04.dir\main.cpp.i

CMakeFiles/Trabalho04.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Trabalho04.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\fbeze\OneDrive\Documentos\Faculdade\LaboratorioDeProgramacao\Trabalho04\main.cpp -o CMakeFiles\Trabalho04.dir\main.cpp.s

# Object files for target Trabalho04
Trabalho04_OBJECTS = \
"CMakeFiles/Trabalho04.dir/main.cpp.obj"

# External object files for target Trabalho04
Trabalho04_EXTERNAL_OBJECTS =

Trabalho04.exe: CMakeFiles/Trabalho04.dir/main.cpp.obj
Trabalho04.exe: CMakeFiles/Trabalho04.dir/build.make
Trabalho04.exe: CMakeFiles/Trabalho04.dir/linklibs.rsp
Trabalho04.exe: CMakeFiles/Trabalho04.dir/objects1.rsp
Trabalho04.exe: CMakeFiles/Trabalho04.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\fbeze\OneDrive\Documentos\Faculdade\LaboratorioDeProgramacao\Trabalho04\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Trabalho04.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Trabalho04.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Trabalho04.dir/build: Trabalho04.exe

.PHONY : CMakeFiles/Trabalho04.dir/build

CMakeFiles/Trabalho04.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Trabalho04.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Trabalho04.dir/clean

CMakeFiles/Trabalho04.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\fbeze\OneDrive\Documentos\Faculdade\LaboratorioDeProgramacao\Trabalho04 C:\Users\fbeze\OneDrive\Documentos\Faculdade\LaboratorioDeProgramacao\Trabalho04 C:\Users\fbeze\OneDrive\Documentos\Faculdade\LaboratorioDeProgramacao\Trabalho04\cmake-build-debug C:\Users\fbeze\OneDrive\Documentos\Faculdade\LaboratorioDeProgramacao\Trabalho04\cmake-build-debug C:\Users\fbeze\OneDrive\Documentos\Faculdade\LaboratorioDeProgramacao\Trabalho04\cmake-build-debug\CMakeFiles\Trabalho04.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Trabalho04.dir/depend

