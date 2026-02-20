cmake_minimum_required(VERSION 3.5)

project(05.homework)

add_executable(random_shuffle random_shuffle.cpp)
set_target_properties(random_shuffle PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(chrono_example chrono_example.cpp
                                istatistics.h
                                min.h
                                max.h
                                mean.h
                                stddev.h
                                percentile.h)
set_target_properties(chrono_example PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(statistics main.cpp)
set_target_properties(statistics PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

