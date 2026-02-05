cmake_minimum_required(VERSION 3.2)
project(guess_number)

set(CMAKE_CXX_STANDARD 20)

add_executable(guess_number 
                main.cpp 
                check_value.h 
                check_value.cpp 
                get_random_target.h 
                get_random_target.cpp
                file_processor.h
                file_processor.cpp)
