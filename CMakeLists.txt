
cmake_minimum_required(VERSION 3.13)

set(CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/cmake/CompilerOptions.cmake")

project(TheRayTracerChallenge
    DESCRIPTION "A C++ implementation of The Ray Tracer Challenge")

find_package(Catch2 CONFIG REQUIRED)
enable_testing()

add_subdirectory(apps)
add_subdirectory(rtc)
add_subdirectory(test)
