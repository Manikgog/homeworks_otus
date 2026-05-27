cmake_minimum_required(VERSION 3.7.2)
project(multi_thread_count CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(multi_thread_count main.cpp
)

if (MSVC)
    target_compile_options(multi_thread_count PUBLIC /W4)
else ()
    target_compile_options(multi_thread_count PUBLIC -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
endif ()