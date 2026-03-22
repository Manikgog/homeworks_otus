cmake_minimum_required(VERSION 3.5)

project(07_homework)

add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
    "googletest"
)

add_executable(
        containers
        src/main.cpp
        src/simple_vector.h
        src/singlelinked_list.h
)

add_executable(
        test_vector
        test/test_vector.cpp
)

add_executable(
        test_list
        test/test_singlelinkedlist.cpp
)

target_include_directories(
        test_vector PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_include_directories(
        test_list PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(
        test_vector PRIVATE
        gtest gtest_main
)

target_link_libraries(
        test_list PRIVATE
        gtest gtest_main
)

set_target_properties(containers
        PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

set_target_properties(test_vector
        PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_compile_options(
        containers PRIVATE
        -Wall -Wextra -pedantic -Werror
)

target_compile_options(
        test_vector PRIVATE
        -Wall -Wextra -pedantic -Werror
)

target_compile_options(
        test_list PRIVATE
        -Wall -Wextra -pedantic -Werror
)