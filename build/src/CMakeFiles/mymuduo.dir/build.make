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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mzy/Code/mymoduo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mzy/Code/mymoduo/build

# Include any dependencies generated for this target.
include src/CMakeFiles/mymuduo.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/mymuduo.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/mymuduo.dir/flags.make

src/CMakeFiles/mymuduo.dir/Channel.cc.o: src/CMakeFiles/mymuduo.dir/flags.make
src/CMakeFiles/mymuduo.dir/Channel.cc.o: ../src/Channel.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mzy/Code/mymoduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/mymuduo.dir/Channel.cc.o"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/Channel.cc.o -c /home/mzy/Code/mymoduo/src/Channel.cc

src/CMakeFiles/mymuduo.dir/Channel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Channel.cc.i"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mzy/Code/mymoduo/src/Channel.cc > CMakeFiles/mymuduo.dir/Channel.cc.i

src/CMakeFiles/mymuduo.dir/Channel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Channel.cc.s"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mzy/Code/mymoduo/src/Channel.cc -o CMakeFiles/mymuduo.dir/Channel.cc.s

src/CMakeFiles/mymuduo.dir/CurrentThread.cc.o: src/CMakeFiles/mymuduo.dir/flags.make
src/CMakeFiles/mymuduo.dir/CurrentThread.cc.o: ../src/CurrentThread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mzy/Code/mymoduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/mymuduo.dir/CurrentThread.cc.o"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/CurrentThread.cc.o -c /home/mzy/Code/mymoduo/src/CurrentThread.cc

src/CMakeFiles/mymuduo.dir/CurrentThread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/CurrentThread.cc.i"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mzy/Code/mymoduo/src/CurrentThread.cc > CMakeFiles/mymuduo.dir/CurrentThread.cc.i

src/CMakeFiles/mymuduo.dir/CurrentThread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/CurrentThread.cc.s"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mzy/Code/mymoduo/src/CurrentThread.cc -o CMakeFiles/mymuduo.dir/CurrentThread.cc.s

src/CMakeFiles/mymuduo.dir/EPollPoller.cc.o: src/CMakeFiles/mymuduo.dir/flags.make
src/CMakeFiles/mymuduo.dir/EPollPoller.cc.o: ../src/EPollPoller.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mzy/Code/mymoduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/mymuduo.dir/EPollPoller.cc.o"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/EPollPoller.cc.o -c /home/mzy/Code/mymoduo/src/EPollPoller.cc

src/CMakeFiles/mymuduo.dir/EPollPoller.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/EPollPoller.cc.i"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mzy/Code/mymoduo/src/EPollPoller.cc > CMakeFiles/mymuduo.dir/EPollPoller.cc.i

src/CMakeFiles/mymuduo.dir/EPollPoller.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/EPollPoller.cc.s"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mzy/Code/mymoduo/src/EPollPoller.cc -o CMakeFiles/mymuduo.dir/EPollPoller.cc.s

src/CMakeFiles/mymuduo.dir/EventLoop.cc.o: src/CMakeFiles/mymuduo.dir/flags.make
src/CMakeFiles/mymuduo.dir/EventLoop.cc.o: ../src/EventLoop.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mzy/Code/mymoduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/mymuduo.dir/EventLoop.cc.o"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/EventLoop.cc.o -c /home/mzy/Code/mymoduo/src/EventLoop.cc

src/CMakeFiles/mymuduo.dir/EventLoop.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/EventLoop.cc.i"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mzy/Code/mymoduo/src/EventLoop.cc > CMakeFiles/mymuduo.dir/EventLoop.cc.i

src/CMakeFiles/mymuduo.dir/EventLoop.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/EventLoop.cc.s"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mzy/Code/mymoduo/src/EventLoop.cc -o CMakeFiles/mymuduo.dir/EventLoop.cc.s

src/CMakeFiles/mymuduo.dir/InetAddress.cc.o: src/CMakeFiles/mymuduo.dir/flags.make
src/CMakeFiles/mymuduo.dir/InetAddress.cc.o: ../src/InetAddress.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mzy/Code/mymoduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/mymuduo.dir/InetAddress.cc.o"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/InetAddress.cc.o -c /home/mzy/Code/mymoduo/src/InetAddress.cc

src/CMakeFiles/mymuduo.dir/InetAddress.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/InetAddress.cc.i"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mzy/Code/mymoduo/src/InetAddress.cc > CMakeFiles/mymuduo.dir/InetAddress.cc.i

src/CMakeFiles/mymuduo.dir/InetAddress.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/InetAddress.cc.s"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mzy/Code/mymoduo/src/InetAddress.cc -o CMakeFiles/mymuduo.dir/InetAddress.cc.s

src/CMakeFiles/mymuduo.dir/Logger.cc.o: src/CMakeFiles/mymuduo.dir/flags.make
src/CMakeFiles/mymuduo.dir/Logger.cc.o: ../src/Logger.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mzy/Code/mymoduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/mymuduo.dir/Logger.cc.o"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/Logger.cc.o -c /home/mzy/Code/mymoduo/src/Logger.cc

src/CMakeFiles/mymuduo.dir/Logger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Logger.cc.i"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mzy/Code/mymoduo/src/Logger.cc > CMakeFiles/mymuduo.dir/Logger.cc.i

src/CMakeFiles/mymuduo.dir/Logger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Logger.cc.s"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mzy/Code/mymoduo/src/Logger.cc -o CMakeFiles/mymuduo.dir/Logger.cc.s

src/CMakeFiles/mymuduo.dir/Poller.cc.o: src/CMakeFiles/mymuduo.dir/flags.make
src/CMakeFiles/mymuduo.dir/Poller.cc.o: ../src/Poller.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mzy/Code/mymoduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/mymuduo.dir/Poller.cc.o"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/Poller.cc.o -c /home/mzy/Code/mymoduo/src/Poller.cc

src/CMakeFiles/mymuduo.dir/Poller.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Poller.cc.i"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mzy/Code/mymoduo/src/Poller.cc > CMakeFiles/mymuduo.dir/Poller.cc.i

src/CMakeFiles/mymuduo.dir/Poller.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Poller.cc.s"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mzy/Code/mymoduo/src/Poller.cc -o CMakeFiles/mymuduo.dir/Poller.cc.s

src/CMakeFiles/mymuduo.dir/TcpServer.cc.o: src/CMakeFiles/mymuduo.dir/flags.make
src/CMakeFiles/mymuduo.dir/TcpServer.cc.o: ../src/TcpServer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mzy/Code/mymoduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/mymuduo.dir/TcpServer.cc.o"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/TcpServer.cc.o -c /home/mzy/Code/mymoduo/src/TcpServer.cc

src/CMakeFiles/mymuduo.dir/TcpServer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/TcpServer.cc.i"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mzy/Code/mymoduo/src/TcpServer.cc > CMakeFiles/mymuduo.dir/TcpServer.cc.i

src/CMakeFiles/mymuduo.dir/TcpServer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/TcpServer.cc.s"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mzy/Code/mymoduo/src/TcpServer.cc -o CMakeFiles/mymuduo.dir/TcpServer.cc.s

src/CMakeFiles/mymuduo.dir/Timestamp.cc.o: src/CMakeFiles/mymuduo.dir/flags.make
src/CMakeFiles/mymuduo.dir/Timestamp.cc.o: ../src/Timestamp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mzy/Code/mymoduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/CMakeFiles/mymuduo.dir/Timestamp.cc.o"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/Timestamp.cc.o -c /home/mzy/Code/mymoduo/src/Timestamp.cc

src/CMakeFiles/mymuduo.dir/Timestamp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Timestamp.cc.i"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mzy/Code/mymoduo/src/Timestamp.cc > CMakeFiles/mymuduo.dir/Timestamp.cc.i

src/CMakeFiles/mymuduo.dir/Timestamp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Timestamp.cc.s"
	cd /home/mzy/Code/mymoduo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mzy/Code/mymoduo/src/Timestamp.cc -o CMakeFiles/mymuduo.dir/Timestamp.cc.s

# Object files for target mymuduo
mymuduo_OBJECTS = \
"CMakeFiles/mymuduo.dir/Channel.cc.o" \
"CMakeFiles/mymuduo.dir/CurrentThread.cc.o" \
"CMakeFiles/mymuduo.dir/EPollPoller.cc.o" \
"CMakeFiles/mymuduo.dir/EventLoop.cc.o" \
"CMakeFiles/mymuduo.dir/InetAddress.cc.o" \
"CMakeFiles/mymuduo.dir/Logger.cc.o" \
"CMakeFiles/mymuduo.dir/Poller.cc.o" \
"CMakeFiles/mymuduo.dir/TcpServer.cc.o" \
"CMakeFiles/mymuduo.dir/Timestamp.cc.o"

# External object files for target mymuduo
mymuduo_EXTERNAL_OBJECTS =

../lib/libmymuduo.so: src/CMakeFiles/mymuduo.dir/Channel.cc.o
../lib/libmymuduo.so: src/CMakeFiles/mymuduo.dir/CurrentThread.cc.o
../lib/libmymuduo.so: src/CMakeFiles/mymuduo.dir/EPollPoller.cc.o
../lib/libmymuduo.so: src/CMakeFiles/mymuduo.dir/EventLoop.cc.o
../lib/libmymuduo.so: src/CMakeFiles/mymuduo.dir/InetAddress.cc.o
../lib/libmymuduo.so: src/CMakeFiles/mymuduo.dir/Logger.cc.o
../lib/libmymuduo.so: src/CMakeFiles/mymuduo.dir/Poller.cc.o
../lib/libmymuduo.so: src/CMakeFiles/mymuduo.dir/TcpServer.cc.o
../lib/libmymuduo.so: src/CMakeFiles/mymuduo.dir/Timestamp.cc.o
../lib/libmymuduo.so: src/CMakeFiles/mymuduo.dir/build.make
../lib/libmymuduo.so: src/CMakeFiles/mymuduo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mzy/Code/mymoduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX shared library ../../lib/libmymuduo.so"
	cd /home/mzy/Code/mymoduo/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mymuduo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/mymuduo.dir/build: ../lib/libmymuduo.so

.PHONY : src/CMakeFiles/mymuduo.dir/build

src/CMakeFiles/mymuduo.dir/clean:
	cd /home/mzy/Code/mymoduo/build/src && $(CMAKE_COMMAND) -P CMakeFiles/mymuduo.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/mymuduo.dir/clean

src/CMakeFiles/mymuduo.dir/depend:
	cd /home/mzy/Code/mymoduo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mzy/Code/mymoduo /home/mzy/Code/mymoduo/src /home/mzy/Code/mymoduo/build /home/mzy/Code/mymoduo/build/src /home/mzy/Code/mymoduo/build/src/CMakeFiles/mymuduo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/mymuduo.dir/depend

