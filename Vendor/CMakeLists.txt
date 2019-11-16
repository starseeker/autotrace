cmake_minimum_required(VERSION 2.8)

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/json11/CMakeLists.txt)
	message(FATAL_ERROR "Git submodules not initialized.  You probably want to run:\ngit submodule update --init\nin ${CMAKE_SOURCE_DIR}")
endif (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/json11/CMakeLists.txt)


add_subdirectory(json11)

if (BUILD_TESTS)
    add_subdirectory(googletest)
endif ()
