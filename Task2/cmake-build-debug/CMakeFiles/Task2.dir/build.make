# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.3.3\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.3.3\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\MyWork\Task2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\MyWork\Task2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\Task2.dir\depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles\Task2.dir\compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles\Task2.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Task2.dir\flags.make

CMakeFiles\Task2.dir\main.cpp.obj: CMakeFiles\Task2.dir\flags.make
CMakeFiles\Task2.dir\main.cpp.obj: C:\MyWork\Task2\main.cpp
CMakeFiles\Task2.dir\main.cpp.obj: CMakeFiles\Task2.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\MyWork\Task2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Task2.dir/main.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\Task2.dir\main.cpp.obj.d --working-dir=C:\MyWork\Task2\cmake-build-debug --filter-prefix="����������: ��������� �����:  " -- C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1435~1.322\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\Task2.dir\main.cpp.obj /FdCMakeFiles\Task2.dir\ /FS -c C:\MyWork\Task2\main.cpp
<<

CMakeFiles\Task2.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Task2.dir/main.cpp.i"
	C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1435~1.322\bin\Hostx86\x86\cl.exe > CMakeFiles\Task2.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\MyWork\Task2\main.cpp
<<

CMakeFiles\Task2.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Task2.dir/main.cpp.s"
	C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1435~1.322\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Task2.dir\main.cpp.s /c C:\MyWork\Task2\main.cpp
<<

CMakeFiles\Task2.dir\GenerateTree.cpp.obj: CMakeFiles\Task2.dir\flags.make
CMakeFiles\Task2.dir\GenerateTree.cpp.obj: C:\MyWork\Task2\GenerateTree.cpp
CMakeFiles\Task2.dir\GenerateTree.cpp.obj: CMakeFiles\Task2.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\MyWork\Task2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Task2.dir/GenerateTree.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\Task2.dir\GenerateTree.cpp.obj.d --working-dir=C:\MyWork\Task2\cmake-build-debug --filter-prefix="����������: ��������� �����:  " -- C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1435~1.322\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\Task2.dir\GenerateTree.cpp.obj /FdCMakeFiles\Task2.dir\ /FS -c C:\MyWork\Task2\GenerateTree.cpp
<<

CMakeFiles\Task2.dir\GenerateTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Task2.dir/GenerateTree.cpp.i"
	C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1435~1.322\bin\Hostx86\x86\cl.exe > CMakeFiles\Task2.dir\GenerateTree.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\MyWork\Task2\GenerateTree.cpp
<<

CMakeFiles\Task2.dir\GenerateTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Task2.dir/GenerateTree.cpp.s"
	C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1435~1.322\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Task2.dir\GenerateTree.cpp.s /c C:\MyWork\Task2\GenerateTree.cpp
<<

CMakeFiles\Task2.dir\MakeOutPut.cpp.obj: CMakeFiles\Task2.dir\flags.make
CMakeFiles\Task2.dir\MakeOutPut.cpp.obj: C:\MyWork\Task2\MakeOutPut.cpp
CMakeFiles\Task2.dir\MakeOutPut.cpp.obj: CMakeFiles\Task2.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\MyWork\Task2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Task2.dir/MakeOutPut.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\Task2.dir\MakeOutPut.cpp.obj.d --working-dir=C:\MyWork\Task2\cmake-build-debug --filter-prefix="����������: ��������� �����:  " -- C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1435~1.322\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\Task2.dir\MakeOutPut.cpp.obj /FdCMakeFiles\Task2.dir\ /FS -c C:\MyWork\Task2\MakeOutPut.cpp
<<

CMakeFiles\Task2.dir\MakeOutPut.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Task2.dir/MakeOutPut.cpp.i"
	C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1435~1.322\bin\Hostx86\x86\cl.exe > CMakeFiles\Task2.dir\MakeOutPut.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\MyWork\Task2\MakeOutPut.cpp
<<

CMakeFiles\Task2.dir\MakeOutPut.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Task2.dir/MakeOutPut.cpp.s"
	C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1435~1.322\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Task2.dir\MakeOutPut.cpp.s /c C:\MyWork\Task2\MakeOutPut.cpp
<<

# Object files for target Task2
Task2_OBJECTS = \
"CMakeFiles\Task2.dir\main.cpp.obj" \
"CMakeFiles\Task2.dir\GenerateTree.cpp.obj" \
"CMakeFiles\Task2.dir\MakeOutPut.cpp.obj"

# External object files for target Task2
Task2_EXTERNAL_OBJECTS =

Task2.exe: CMakeFiles\Task2.dir\main.cpp.obj
Task2.exe: CMakeFiles\Task2.dir\GenerateTree.cpp.obj
Task2.exe: CMakeFiles\Task2.dir\MakeOutPut.cpp.obj
Task2.exe: CMakeFiles\Task2.dir\build.make
Task2.exe: CMakeFiles\Task2.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\MyWork\Task2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Task2.exe"
	"C:\Program Files\JetBrains\CLion 2022.3.3\bin\cmake\win\x64\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Task2.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100220~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100220~1.0\x86\mt.exe --manifests -- C:\PROGRA~1\MIB055~1\2022\COMMUN~1\VC\Tools\MSVC\1435~1.322\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Task2.dir\objects1.rsp @<<
 /out:Task2.exe /implib:Task2.lib /pdb:C:\MyWork\Task2\cmake-build-debug\Task2.pdb /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Task2.dir\build: Task2.exe
.PHONY : CMakeFiles\Task2.dir\build

CMakeFiles\Task2.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Task2.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Task2.dir\clean

CMakeFiles\Task2.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\MyWork\Task2 C:\MyWork\Task2 C:\MyWork\Task2\cmake-build-debug C:\MyWork\Task2\cmake-build-debug C:\MyWork\Task2\cmake-build-debug\CMakeFiles\Task2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\Task2.dir\depend

