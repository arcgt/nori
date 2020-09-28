# Install script for directory: /Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf

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
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/lib/libIlmImf.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/lib" TYPE STATIC_LIBRARY FILES "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p-build/IlmImf/libIlmImf.a")
  if(EXISTS "$ENV{DESTDIR}/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/lib/libIlmImf.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/lib/libIlmImf.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/lib/libIlmImf.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfForward.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfExport.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfBoxAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfCRgbaFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfChannelList.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfChannelListAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfCompressionAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfDoubleAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfFloatAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfFrameBuffer.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfHeader.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfIO.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfInputFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfIntAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfLineOrderAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfMatrixAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfOpaqueAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfOutputFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfRgbaFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfStringAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfVecAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfHuf.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfWav.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfLut.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfArray.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfCompression.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfLineOrder.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfName.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfPixelType.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfVersion.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfXdr.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfConvert.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfPreviewImage.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfPreviewImageAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfChromaticities.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfChromaticitiesAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfKeyCode.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfKeyCodeAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfTimeCode.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfTimeCodeAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfRational.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfRationalAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfFramesPerSecond.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfStandardAttributes.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfEnvmap.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfEnvmapAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfInt64.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfRgba.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfTileDescription.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfTileDescriptionAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfTiledInputFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfTiledOutputFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfTiledRgbaFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfRgbaYca.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfTestFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfThreading.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfB44Compressor.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfStringVectorAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfMultiView.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfAcesFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfMultiPartOutputFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfGenericOutputFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfMultiPartInputFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfGenericInputFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfPartType.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfPartHelper.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfOutputPart.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfTiledOutputPart.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfInputPart.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfTiledInputPart.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfDeepScanLineOutputFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfDeepScanLineOutputPart.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfDeepScanLineInputFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfDeepScanLineInputPart.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfDeepTiledInputFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfDeepTiledInputPart.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfDeepTiledOutputFile.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfDeepTiledOutputPart.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfDeepFrameBuffer.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfDeepCompositing.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfCompositeDeepScanLine.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfNamespace.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfMisc.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfDeepImageState.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfDeepImageStateAttribute.h;/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR/ImfFloatVectorAttribute.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/dist/include/OpenEXR" TYPE FILE FILES
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfForward.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfExport.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfBoxAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfCRgbaFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfChannelList.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfChannelListAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfCompressionAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDoubleAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfFloatAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfFrameBuffer.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfHeader.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfIO.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfInputFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfIntAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfLineOrderAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfMatrixAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfOpaqueAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfOutputFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfRgbaFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfStringAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfVecAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfHuf.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfWav.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfLut.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfArray.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfCompression.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfLineOrder.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfName.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfPixelType.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfVersion.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfXdr.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfConvert.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfPreviewImage.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfPreviewImageAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfChromaticities.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfChromaticitiesAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfKeyCode.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfKeyCodeAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTimeCode.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTimeCodeAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfRational.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfRationalAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfFramesPerSecond.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfStandardAttributes.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfEnvmap.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfEnvmapAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfInt64.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfRgba.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTileDescription.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTileDescriptionAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTiledInputFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTiledOutputFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTiledRgbaFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfRgbaYca.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTestFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfThreading.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfB44Compressor.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfStringVectorAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfMultiView.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfAcesFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfMultiPartOutputFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfGenericOutputFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfMultiPartInputFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfGenericInputFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfPartType.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfPartHelper.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfOutputPart.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTiledOutputPart.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfInputPart.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTiledInputPart.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepScanLineOutputFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepScanLineOutputPart.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepScanLineInputFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepScanLineInputPart.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepTiledInputFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepTiledInputPart.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepTiledOutputFile.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepTiledOutputPart.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepFrameBuffer.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepCompositing.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfCompositeDeepScanLine.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfNamespace.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfMisc.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepImageState.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepImageStateAttribute.h"
    "/Users/tian/Documents/University/Master/ComputerGraphics/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfFloatVectorAttribute.h"
    )
endif()

