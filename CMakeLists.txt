cmake_minimum_required(VERSION 2.8)
project(sylar)

# include (cmake/utils.cmake)

set (CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wbuiltin-macro-redefined")

include_directories(.)
include_directories(/apps/sylar/include)
link_directories(/usr/local/lib64)


set(LIB_SRC
sylar/log.cpp
sylar/util.cpp
sylar/config.cpp
sylar/thread.cpp
)

find_library(YAMLCPP yaml-cpp)
message("***" , ${YAMLCPP})

add_library(sylar SHARED ${LIB_SRC})
# force_redefine_file_macro_for_source(sylar)

set(LIB_LIB
    sylar
    pthread
    ${YAMLCPP}
    )

add_executable(test tests/test.cpp)
add_dependencies(test sylar)
# force_redefine_file_macro_for_source(test)
target_link_libraries(test sylar ${LIB_LIB})

add_executable(test_config tests/test_config.cpp)
add_dependencies(test_config sylar)
# force_redefine_file_macro_for_source(test_config)
target_link_libraries(test_config sylar ${LIB_LIB})

add_executable(test_thread tests/test_thread.cpp)
add_dependencies(test_thread sylar)
# force_redefine_file_macro_for_source(test_config)
target_link_libraries(test_thread sylar ${LIB_LIB})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)