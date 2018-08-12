cmake_minimum_required(VERSION 3.2)

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
add_executable(autotraceCpp main.cpp)

set_target_properties(autotraceCpp PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )

target_link_libraries(autotraceCpp PUBLIC autotraceCppLib)

if (EMSCRIPTEN)
    set_target_properties(autotraceCpp PROPERTIES LINK_FLAGS
            "-s WASM=1 -s USE_LIBPNG=1 --emrun --embed-file ${CMAKE_CURRENT_SOURCE_DIR}/../../assets/@/assets/")
    target_compile_definitions(autotraceCpp PRIVATE ASSET_PATH="/assets/")
else ()
    target_compile_definitions(autotraceCpp PRIVATE ASSET_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../../asset")
endif ()
