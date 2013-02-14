CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_ALLOW_LOSSE_LOOP_CONSTRUCTS ON)

message(STATUS "#####################################################################")
message(STATUS "# TheLord Engine Build System")
message(STATUS "#####################################################################")
message(STATUS "Configuring build system...")
message(STATUS "CMake version: ${CMAKE_VERSION}")

# CMake 2.8.2 has a bug that creates unusable Xcode projects when using ARCHS_STANDARD_32_BIT
# to specify both armv6 and armv7.
#if(CMAKE_VERSION VERSION_EQUAL 2.8.2)
#	message(FATAL_ERROR "CMake 2.8.2 cannot create compatible Xcode projects for iOS")
#endif()

if (APPLE)
	option(LORD_BUILD_PLATFORM_IOS "Mac iOS platform." TRUE)
endif ()

# Use relative paths
# This is mostly to reduce path size for command-line limits on windows
if(WIN32)
	message(STATUS "Platform: Windows")
# This seems to break Xcode projects so definitely don't enable on Apple builds
	set(CMAKE_USE_RELATIVE_PATHS true)
	set(CMAKE_SUPPRESS_REGENERATION true)
elseif (UNIX)
	if (APPLE)
		include(CMakeForceCompiler)
		CMAKE_FORCE_C_COMPILER(clang GNU)
		CMAKE_FORCE_CXX_COMPILER(clang++ GNU)
		SET(CMAKE_SIZEOF_VOID_P 4)
		set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvm.clang.1_0")
		
		if (LORD_BUILD_PLATFORM_IOS)
			message(STATUS "Platform: Mac iOS")
		else ()
			message(STATUS "Platform: MacOSX")
		endif ()
	else ()
		message(STATUS "Platform: Unix/Linux")
	endif ()
else ()
	message(STATUS "Platform: Unknown")
endif ()


project(Lord)


message(STATUS "Set Environment Variables...")

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

if(WIN32)
	set(LORD_SDK_PATH "${PROJECT_SOURCE_DIR}/SDK/Windows")
elseif (UNIX)
	if (APPLE)
		if (LORD_BUILD_PLATFORM_IOS)
			set(LORD_SDK_PATH "${PROJECT_SOURCE_DIR}/SDK/iOS")
		else ()
			set(LORD_SDK_PATH "${PROJECT_SOURCE_DIR}/SDK/OSX")
		endif ()
	else ()
	endif ()
endif ()

set(LORD_SRC_PATH "${PROJECT_SOURCE_DIR}/Src")
set(LIBRARY_OUTPUT_PATH "${LORD_SDK_PATH}/lib/${CMAKE_BUILD_TYPE}")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Bin)
set(LORD_BIN_PATH "${EXECUTABLE_OUTPUT_PATH}")
set(LORD_DEP_PATH "${PROJECT_SOURCE_DIR}/Dependencies")
set(LORD_DOC_PATH "${PROJECT_SOURCE_DIR}/Docs")

message(STATUS "\${CMAKE_BUILD_TYPE}: ${CMAKE_BUILD_TYPE}")

message(STATUS "\${PROJECT_SOURCE_DIR}: ${PROJECT_SOURCE_DIR}")
message(STATUS "\${PROJECT_BINARY_DIR}: ${PROJECT_BINARY_DIR}")
message(STATUS "\${LIBRARY_OUTPUT_PATH}: ${LIBRARY_OUTPUT_PATH}")
message(STATUS "\${LORD_SRC_PATH}: ${LORD_SRC_PATH}")
message(STATUS "\${LORD_DEP_PATH}: ${LORD_DEP_PATH}")
message(STATUS "\${LORD_SDK_PATH}: ${LORD_SDK_PATH}")
message(STATUS "\${LORD_DOC_PATH}: ${LORD_DOC_PATH}")

# Add sub directories
ADD_SUBDIRECTORY(Src)

# Include necessary submodules
#ADD_SUBDIRECTORY(libhello)