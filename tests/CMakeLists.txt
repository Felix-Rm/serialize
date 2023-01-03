cmake_minimum_required(VERSION 3.1)
enable_testing()

if(NOT TARGET serialize_test_suite)
    project(serialize_test_suite)

    add_executable(serialize_test_suite
        testing.cpp
    )

    target_include_directories(serialize_test_suite PRIVATE ../src/)
    target_include_directories(serialize_test_suite PRIVATE ../dependencies/)

    target_link_libraries(serialize_test_suite PRIVATE ftest)

    target_compile_options(serialize_test_suite PRIVATE -std=c++17 -pedantic
        -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Wconversion -Wsign-conversion -Wmisleading-indentation
        -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wextra-semi)

    if(NOT DEFINED DISABLE_ASAN)
        target_compile_options(serialize_test_suite PRIVATE -fsanitize=address)
        target_link_options(serialize_test_suite PRIVATE -lasan)
    else()
        message("WARNING: address sanitizer has been disabled, memory access errors may not be detected")
    endif()

    add_test(serialize_test_suite serialize_test_suite)
endif()