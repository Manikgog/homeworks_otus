cmake_minimum_required(VERSION 3.5)

project(07_homework)

# Устанавливаем стандарт C++ для всего проекта
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Общие флаги компиляции для всех целей
set(COMMON_COMPILE_FLAGS -Wall -Wextra -pedantic -Werror)

# Подключаем Google Test
add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
        "${CMAKE_CURRENT_BINARY_DIR}/googletest"
)

# Исполняемый файл с примерами использования контейнеров
add_executable(
        containers
        src/main.cpp
        src/simple_vector.h
        src/singlelinked_list.h
)

target_compile_options(containers PRIVATE ${COMMON_COMPILE_FLAGS})

add_executable(
        containers_tests
        test/test_vector.cpp
        test/test_singlelinkedlist.cpp
)

target_include_directories(
        containers_tests PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(
        containers_tests PRIVATE
        gtest
        gtest_main
)

target_compile_options(containers_tests PRIVATE ${COMMON_COMPILE_FLAGS})
