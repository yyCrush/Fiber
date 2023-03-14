cmake_minimum_required(VERSION 2.8)
project(myfiber)

# include (cmake/utils.cmake)

set (CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic  -g -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wbuiltin-macro-redefined")

include_directories(.)
include_directories(/apps/myfiber/include)
link_directories(/usr/local/lib64)


set(LIB_SRC
myfiber/log.cpp
myfiber/fiber.cpp
myfiber/util.cpp
myfiber/config.cpp
myfiber/thread.cpp
myfiber/scheduler.cpp
myfiber/iomanager.cpp
myfiber/timer.cpp
myfiber/hook.cpp
myfiber/fd_manager.cpp
myfiber/address.cpp
myfiber/socket.cpp
myfiber/tcp_server.cpp
myfiber/http/http.cpp
myfiber/http/http_parser.cpp
myfiber/http/http11_parser.cpp
myfiber/http/httpclient_parser.cpp
)

find_library(YAMLCPP yaml-cpp)
message("***" , ${YAMLCPP})

add_library(myfiber SHARED ${LIB_SRC})
# force_redefine_file_macro_for_source(myfiber)

set(LIB_LIB
    myfiber
    pthread
    dl
    ${YAMLCPP}
    )

add_executable(test tests/test.cpp)
add_dependencies(test myfiber)
# force_redefine_file_macro_for_source(test)
target_link_libraries(test myfiber ${LIB_LIB})

add_executable(test_config tests/test_config.cpp)
add_dependencies(test_config myfiber)
# force_redefine_file_macro_for_source(test_config)
target_link_libraries(test_config myfiber ${LIB_LIB})

add_executable(test_thread tests/test_thread.cpp)
add_dependencies(test_thread myfiber)
# force_redefine_file_macro_for_source(test_config)
target_link_libraries(test_thread myfiber ${LIB_LIB})

add_executable(test_util tests/test_util.cpp)
add_dependencies(test_util myfiber)
# force_redefine_file_macro_for_source(test_config)
target_link_libraries(test_util myfiber ${LIB_LIB})

add_executable(test_fiber tests/test_fiber.cpp)
add_dependencies(test_fiber myfiber)
# force_redefine_file_macro_for_source(test_config)
target_link_libraries(test_fiber myfiber ${LIB_LIB})

add_executable(test_scheduler tests/test_scheduler.cpp)
add_dependencies(test_scheduler myfiber)
# force_redefine_file_macro_for_source(test_config)
target_link_libraries(test_scheduler myfiber ${LIB_LIB})

add_executable(test_iomanager tests/test_iomanager.cpp)
add_dependencies(test_iomanager myfiber)
# force_redefine_file_macro_for_source(test_config)
target_link_libraries(test_iomanager myfiber ${LIB_LIB})

add_executable(test_address tests/test_address.cpp)
add_dependencies(test_address myfiber)
# force_redefine_file_macro_for_source(test_config)
target_link_libraries(test_address myfiber ${LIB_LIB})

add_executable(test_hook tests/test_hook.cpp)
add_dependencies(test_hook myfiber)
# force_redefine_file_macro_for_source(test_config)
target_link_libraries(test_hook myfiber ${LIB_LIB})

add_executable(test_socket tests/test_socket.cpp)
add_dependencies(test_socket myfiber)
# force_redefine_file_macro_for_source(test_config)
target_link_libraries(test_socket myfiber ${LIB_LIB})

add_executable(test_http_parser tests/test_http_parser.cpp)
add_dependencies(test_http_parser myfiber)
# force_redefine_file_macro_for_source(test_config)
target_link_libraries(test_http_parser myfiber ${LIB_LIB})

add_executable(test_tcp_server tests/test_tcp_server.cpp)
add_dependencies(test_tcp_server myfiber)
# force_redefine_file_macro_for_source(test_config)
target_link_libraries(test_tcp_server myfiber ${LIB_LIB})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)