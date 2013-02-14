message(STATUS "Configuring module: Core …")

include_directories(
  ${LORD_SRC_PATH}/Core
  ${LORD_DEP_PATH}/nedmalloc/Include
)

set(LIB_SRC 
  CoreStd.cpp
  Util/StringUtil.cpp
  Util/AssertX.cpp
  Util/Guid.cpp
  Util/PathUtil.cpp
  Memory/MemTracker.cpp
  Memory/MemNedPooling.cpp
  Memory/MemAllocObj.cpp
  Memory/LordMemory.cpp
  Math/LordMath.cpp
  Math/Vec2.cpp
  Math/Vec3.cpp
  Math/Vec4.cpp
  Math/Mat.cpp
  #Math/MathLib.cpp
)

ADD_DEFINITIONS("-DLORD_CORE_EXPORTS")
ADD_LIBRARY(libCore SHARED ${LIB_SRC})
SET_TARGET_PROPERTIES(libCore PROPERTIES OUTPUT_NAME "LordCore")

message(STATUS "Configure success!")