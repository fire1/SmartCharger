# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = "C:\Program Files (x86)\JetBrains\CLion 2016.3\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\JetBrains\CLion 2016.3\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Admin\Documents\Arduino\SmartCharger

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Admin\Documents\Arduino\SmartCharger\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SmartCharger.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SmartCharger.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SmartCharger.dir/flags.make

SmartCharger_SmartCharger.ino.cpp: ../SmartCharger.ino
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\Admin\Documents\Arduino\SmartCharger\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Regnerating SmartCharger.ino Sketch"
	"C:\Program Files (x86)\JetBrains\CLion 2016.3\bin\cmake\bin\cmake.exe" C:/Users/Admin/Documents/Arduino/SmartCharger

CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.obj: CMakeFiles/SmartCharger.dir/flags.make
CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.obj: SmartCharger_SmartCharger.ino.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Admin\Documents\Arduino\SmartCharger\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SmartCharger.dir\SmartCharger_SmartCharger.ino.cpp.obj -c C:\Users\Admin\Documents\Arduino\SmartCharger\cmake-build-debug\SmartCharger_SmartCharger.ino.cpp

CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Admin\Documents\Arduino\SmartCharger\cmake-build-debug\SmartCharger_SmartCharger.ino.cpp > CMakeFiles\SmartCharger.dir\SmartCharger_SmartCharger.ino.cpp.i

CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Admin\Documents\Arduino\SmartCharger\cmake-build-debug\SmartCharger_SmartCharger.ino.cpp -o CMakeFiles\SmartCharger.dir\SmartCharger_SmartCharger.ino.cpp.s

CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.obj.requires:

.PHONY : CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.obj.requires

CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.obj.provides: CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.obj.requires
	$(MAKE) -f CMakeFiles\SmartCharger.dir\build.make CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.obj.provides.build
.PHONY : CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.obj.provides

CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.obj.provides.build: CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.obj


# Object files for target SmartCharger
SmartCharger_OBJECTS = \
"CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.obj"

# External object files for target SmartCharger
SmartCharger_EXTERNAL_OBJECTS =

SmartCharger.elf: CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.obj
SmartCharger.elf: CMakeFiles/SmartCharger.dir/build.make
SmartCharger.elf: libuno_Wire.a
SmartCharger.elf: libuno_twi.a
SmartCharger.elf: libuno_CORE.a
SmartCharger.elf: CMakeFiles/SmartCharger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Admin\Documents\Arduino\SmartCharger\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable SmartCharger.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\SmartCharger.dir\link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating EEP image"
	"C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avr-objcopy.exe" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 C:/Users/Admin/Documents/Arduino/SmartCharger/cmake-build-debug/SmartCharger.elf C:/Users/Admin/Documents/Arduino/SmartCharger/cmake-build-debug/SmartCharger.eep
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating HEX image"
	"C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avr-objcopy.exe" -O ihex -R .eeprom C:/Users/Admin/Documents/Arduino/SmartCharger/cmake-build-debug/SmartCharger.elf C:/Users/Admin/Documents/Arduino/SmartCharger/cmake-build-debug/SmartCharger.hex
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Calculating image size"
	"C:\Program Files (x86)\JetBrains\CLion 2016.3\bin\cmake\bin\cmake.exe" -DFIRMWARE_IMAGE=C:/Users/Admin/Documents/Arduino/SmartCharger/cmake-build-debug/SmartCharger.elf -DMCU=atmega328p -DEEPROM_IMAGE=C:/Users/Admin/Documents/Arduino/SmartCharger/cmake-build-debug/SmartCharger.eep -P C:/Users/Admin/Documents/Arduino/SmartCharger/cmake-build-debug/CMakeFiles/FirmwareSize.cmake

# Rule to build all files generated by this target.
CMakeFiles/SmartCharger.dir/build: SmartCharger.elf

.PHONY : CMakeFiles/SmartCharger.dir/build

CMakeFiles/SmartCharger.dir/requires: CMakeFiles/SmartCharger.dir/SmartCharger_SmartCharger.ino.cpp.obj.requires

.PHONY : CMakeFiles/SmartCharger.dir/requires

CMakeFiles/SmartCharger.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\SmartCharger.dir\cmake_clean.cmake
.PHONY : CMakeFiles/SmartCharger.dir/clean

CMakeFiles/SmartCharger.dir/depend: SmartCharger_SmartCharger.ino.cpp
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Admin\Documents\Arduino\SmartCharger C:\Users\Admin\Documents\Arduino\SmartCharger C:\Users\Admin\Documents\Arduino\SmartCharger\cmake-build-debug C:\Users\Admin\Documents\Arduino\SmartCharger\cmake-build-debug C:\Users\Admin\Documents\Arduino\SmartCharger\cmake-build-debug\CMakeFiles\SmartCharger.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SmartCharger.dir/depend

