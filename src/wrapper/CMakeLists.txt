cmake_minimum_required(VERSION 3.2)

cmake_policy(SET CMP0048 NEW)
project(autotraceCpp)

add_library(autotraceCppLib
        Autotrace.cpp
        Options.cpp
        FittingOptionsBuidler.cpp
        InputOptionsBuilder.cpp
        OutputOptionsBuilder.cpp
        OutputOptions.cpp
        InputOptions.cpp
        FittingOptions.cpp
        Json/JsonHelper.cpp)

target_include_directories(autotraceCppLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} Json)

set_target_properties(autotraceCppLib PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )

target_link_libraries(autotraceCppLib PUBLIC autotraceLib json11)

# Wrapper cmd test.
add_executable(autotraceCpp autotrace.cpp)

set_target_properties(autotraceCpp PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )

target_link_libraries(autotraceCpp PUBLIC autotraceCppLib)

if (EMSCRIPTEN)
    set_target_properties(autotraceCpp PROPERTIES LINK_FLAGS
            "--bind -s WASM=1 -s DISABLE_EXCEPTION_CATCHING=0 -s ALLOW_MEMORY_GROWTH=1 -s USE_LIBPNG=1 -s NO_EXIT_RUNTIME=1 -s MODULARIZE=1 --embed-file ${CMAKE_CURRENT_SOURCE_DIR}/../../assets/@/assets/")
    target_compile_options(autotraceCpp PRIVATE --bind)
    target_compile_definitions(autotraceCpp PRIVATE ASSET_PATH="/assets/")
else ()
    target_compile_definitions(autotraceCpp PRIVATE ASSET_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../../assets/")
endif ()
