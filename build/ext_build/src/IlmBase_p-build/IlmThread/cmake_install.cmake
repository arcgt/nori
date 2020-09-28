# Install script for directory: /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/IlmBase_p/IlmThread

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/IlmBase_p-build/IlmThread/libIlmThread.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmThread.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmThread.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmThread.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/IlmBase_p/IlmThread/IlmThreadPool.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/IlmBase_p/IlmThread/IlmThread.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/IlmBase_p/IlmThread/IlmThreadSemaphore.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/IlmBase_p/IlmThread/IlmThreadMutex.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/IlmBase_p/IlmThread/IlmThreadNamespace.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/IlmBase_p/IlmThread/IlmThreadExport.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/IlmBase_p/IlmThread/IlmThreadForward.h"
    )
endif()

