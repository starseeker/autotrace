cmake_minimum_required(VERSION 3.8)

add_executable(autotraceWrapperTests
        main.cpp
        OutputOptionsTests.cpp
        InputOptionsTests.cpp
        FittingOptionsTests.cpp
        )

set_target_properties(autotraceWrapperTests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )

target_link_libraries(autotraceWrapperTests PRIVATE autotraceCppLib gtest)
