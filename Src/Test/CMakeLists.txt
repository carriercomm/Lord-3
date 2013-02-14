message(STATUS "Configuring module: Test …")

include_directories(
  ${LORD_SRC_PATH}/Core
  ${LORD_DEP_PATH}/nedmalloc/Include
)

LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH})

set(APP_SRC 
  main.cpp
)

ADD_EXECUTABLE(test ${APP_SRC})
TARGET_LINK_LIBRARIES(test libCore)

message(STATUS "Configure success!")