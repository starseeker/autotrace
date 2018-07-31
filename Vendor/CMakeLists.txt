cmake_minimum_required(VERSION 2.8)

add_subdirectory(json11)

if (BUILD_TESTS)
    add_subdirectory(googletest)
endif ()
