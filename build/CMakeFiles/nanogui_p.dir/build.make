# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Users/tian/opt/anaconda3/envs/cg/bin/cmake

# The command to remove a file.
RM = /Users/tian/opt/anaconda3/envs/cg/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/tian/Documents/University/Master/ComputerGraphics/nori

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tian/Documents/University/Master/ComputerGraphics/nori/build

# Utility rule file for nanogui_p.

# Include the progress variables for this target.
include CMakeFiles/nanogui_p.dir/progress.make

CMakeFiles/nanogui_p: CMakeFiles/nanogui_p-complete


CMakeFiles/nanogui_p-complete: ext_build/src/nanogui_p-stamp/nanogui_p-install
CMakeFiles/nanogui_p-complete: ext_build/src/nanogui_p-stamp/nanogui_p-mkdir
CMakeFiles/nanogui_p-complete: ext_build/src/nanogui_p-stamp/nanogui_p-download
CMakeFiles/nanogui_p-complete: ext_build/src/nanogui_p-stamp/nanogui_p-update
CMakeFiles/nanogui_p-complete: ext_build/src/nanogui_p-stamp/nanogui_p-patch
CMakeFiles/nanogui_p-complete: ext_build/src/nanogui_p-stamp/nanogui_p-configure
CMakeFiles/nanogui_p-complete: ext_build/src/nanogui_p-stamp/nanogui_p-build
CMakeFiles/nanogui_p-complete: ext_build/src/nanogui_p-stamp/nanogui_p-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'nanogui_p'"
	/Users/tian/opt/anaconda3/envs/cg/bin/cmake -E make_directory /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/CMakeFiles
	/Users/tian/opt/anaconda3/envs/cg/bin/cmake -E touch /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/CMakeFiles/nanogui_p-complete
	/Users/tian/opt/anaconda3/envs/cg/bin/cmake -E touch /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-stamp/nanogui_p-done

ext_build/src/nanogui_p-stamp/nanogui_p-install: ext_build/src/nanogui_p-stamp/nanogui_p-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Performing install step for 'nanogui_p'"
	cd /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-build && $(MAKE) install
	cd /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-build && /Users/tian/opt/anaconda3/envs/cg/bin/cmake -E touch /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-stamp/nanogui_p-install

ext_build/src/nanogui_p-stamp/nanogui_p-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'nanogui_p'"
	/Users/tian/opt/anaconda3/envs/cg/bin/cmake -E make_directory /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p
	/Users/tian/opt/anaconda3/envs/cg/bin/cmake -E make_directory /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-build
	/Users/tian/opt/anaconda3/envs/cg/bin/cmake -E make_directory /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build
	/Users/tian/opt/anaconda3/envs/cg/bin/cmake -E make_directory /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/tmp
	/Users/tian/opt/anaconda3/envs/cg/bin/cmake -E make_directory /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-stamp
	/Users/tian/opt/anaconda3/envs/cg/bin/cmake -E make_directory /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src
	/Users/tian/opt/anaconda3/envs/cg/bin/cmake -E make_directory /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-stamp
	/Users/tian/opt/anaconda3/envs/cg/bin/cmake -E touch /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-stamp/nanogui_p-mkdir

ext_build/src/nanogui_p-stamp/nanogui_p-download: ext_build/src/nanogui_p-stamp/nanogui_p-urlinfo.txt
ext_build/src/nanogui_p-stamp/nanogui_p-download: ext_build/src/nanogui_p-stamp/nanogui_p-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (DIR copy) for 'nanogui_p'"
	cd /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src && /Users/tian/opt/anaconda3/envs/cg/bin/cmake -E rm -rf /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p
	cd /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src && /Users/tian/opt/anaconda3/envs/cg/bin/cmake -E copy_directory /Users/tian/Documents/University/Master/ComputerGraphics/nori/ext/nanogui /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p
	cd /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src && /Users/tian/opt/anaconda3/envs/cg/bin/cmake -E touch /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-stamp/nanogui_p-download

ext_build/src/nanogui_p-stamp/nanogui_p-update: ext_build/src/nanogui_p-stamp/nanogui_p-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No update step for 'nanogui_p'"
	/Users/tian/opt/anaconda3/envs/cg/bin/cmake -E echo_append
	/Users/tian/opt/anaconda3/envs/cg/bin/cmake -E touch /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-stamp/nanogui_p-update

ext_build/src/nanogui_p-stamp/nanogui_p-patch: ext_build/src/nanogui_p-stamp/nanogui_p-update
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "No patch step for 'nanogui_p'"
	/Users/tian/opt/anaconda3/envs/cg/bin/cmake -E echo_append
	/Users/tian/opt/anaconda3/envs/cg/bin/cmake -E touch /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-stamp/nanogui_p-patch

ext_build/src/nanogui_p-stamp/nanogui_p-configure: ext_build/tmp/nanogui_p-cfgcmd.txt
ext_build/src/nanogui_p-stamp/nanogui_p-configure: ext_build/src/nanogui_p-stamp/nanogui_p-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Performing configure step for 'nanogui_p'"
	cd /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-build && /Users/tian/opt/anaconda3/envs/cg/bin/cmake -DCMAKE_BUILD_TYPE=Release "-DCMAKE_GENERATOR=Unix Makefiles" -Wno-dev -DCMAKE_INSTALL_PREFIX=/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist -DCMAKE_OSX_DEPLOYMENT_TARGET=10.15 -DCMAKE_OSX_SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk -D "CMAKE_EXTERNAL_ARGUMENTS:STRING=-DCMAKE_BUILD_TYPE=Release\$$-DCMAKE_GENERATOR=Unix Makefiles\$$-Wno-dev\$$-DCMAKE_INSTALL_PREFIX=/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist\$$-DCMAKE_OSX_DEPLOYMENT_TARGET=10.15\$$-DCMAKE_OSX_SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk" "-GUnix Makefiles" /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p
	cd /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-build && /Users/tian/opt/anaconda3/envs/cg/bin/cmake -E touch /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-stamp/nanogui_p-configure

ext_build/src/nanogui_p-stamp/nanogui_p-build: ext_build/src/nanogui_p-stamp/nanogui_p-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Performing build step for 'nanogui_p'"
	cd /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-build && $(MAKE)
	cd /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-build && /Users/tian/opt/anaconda3/envs/cg/bin/cmake -E touch /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/nanogui_p-stamp/nanogui_p-build

nanogui_p: CMakeFiles/nanogui_p
nanogui_p: CMakeFiles/nanogui_p-complete
nanogui_p: ext_build/src/nanogui_p-stamp/nanogui_p-install
nanogui_p: ext_build/src/nanogui_p-stamp/nanogui_p-mkdir
nanogui_p: ext_build/src/nanogui_p-stamp/nanogui_p-download
nanogui_p: ext_build/src/nanogui_p-stamp/nanogui_p-update
nanogui_p: ext_build/src/nanogui_p-stamp/nanogui_p-patch
nanogui_p: ext_build/src/nanogui_p-stamp/nanogui_p-configure
nanogui_p: ext_build/src/nanogui_p-stamp/nanogui_p-build
nanogui_p: CMakeFiles/nanogui_p.dir/build.make

.PHONY : nanogui_p

# Rule to build all files generated by this target.
CMakeFiles/nanogui_p.dir/build: nanogui_p

.PHONY : CMakeFiles/nanogui_p.dir/build

CMakeFiles/nanogui_p.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nanogui_p.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nanogui_p.dir/clean

CMakeFiles/nanogui_p.dir/depend:
	cd /Users/tian/Documents/University/Master/ComputerGraphics/nori/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/tian/Documents/University/Master/ComputerGraphics/nori /Users/tian/Documents/University/Master/ComputerGraphics/nori /Users/tian/Documents/University/Master/ComputerGraphics/nori/build /Users/tian/Documents/University/Master/ComputerGraphics/nori/build /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/CMakeFiles/nanogui_p.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/nanogui_p.dir/depend
