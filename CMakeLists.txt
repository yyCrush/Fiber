cmake_minimum_required(VERSION 2.8)
project(sylar)

set (CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(.)
include_directories(/apps/sylar/include)
link_directories(/usr/local/lib64)

find_library(YAMLCPP yaml-cpp)
message("***", ${YAMLCPP})

set(LIB_SRC
    sylar/log.cpp
    sylar/util.cpp
    sylar/config.cpp
    )
add_library(sylar SHARED ${LIB_SRC})

add_executable(test tests/test.cpp)
add_dependencies(test sylar)
target_link_libraries(test sylar ${YAMLCPP})

add_executable(test_config tests/test_config.cpp)
add_dependencies(test_config sylar)
target_link_libraries(test_config sylar yaml-cpp)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)