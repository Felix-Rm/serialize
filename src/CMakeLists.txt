cmake_minimum_required(VERSION 3.1)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY CMAKE_EXPORT_COMPILE_COMMANDS ON)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/src/" # source directory
        DESTINATION "include/serialize" # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.hpp" # select header files
        PATTERN "build" EXCLUDE
        PATTERN "tests" EXCLUDE
        PATTERN ".*" EXCLUDE
        PATTERN "**CMakeFiles**" EXCLUDE)
