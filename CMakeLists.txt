cmake_minimum_required(VERSION 3.1)
enable_testing()
project(lw_std_build)

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

add_subdirectory(dependencies/ftest)
add_subdirectory(tests)