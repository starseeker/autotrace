cmake_minimum_required(VERSION 3.8)

option(BUILD_TESTS "Builds tests mostly for testing the wrapper" OFF)

if (NOT EMSCRIPTEN)
    find_package(ImageMagick COMPONENTS MagickCore)
    find_package(PNG)
## TODO CHECK for SWF
## TODO CHECK for PSTOEDIT
endif ()

add_library(autotraceLib
        src/fit.c
        src/bitmap.c
        src/spline.c
        src/curve.c
        src/epsilon-equal.c
        src/vector.c
        src/color.c
        src/autotrace.c
        src/despeckle.c
        src/output.cpp
        src/input.cpp
        src/pxl-outline.c
        src/median.c
        src/thin-image.c
        src/logreport.c
        src/filename.c
        src/exception.c
        src/strgicmp.c
        src/image-proc.c
        src/module.c
        src/input-pnm.c
        src/input-bmp.c
        src/input-tga.c
        src/input-gf.c
        src/output-eps.c
        src/output-er.c
        src/output-fig.c
        src/output-sk.c
        src/output-svg.c
        src/output-ugs.c
        src/output-p2e.c
        src/output-emf.c
        src/output-dxf.c
        src/output-epd.c
        src/output-pdf.c
        src/output-mif.c
        src/output-cgm.c
        src/output-dr2d.c
        src/output-pov.c
        src/output-plt.c
        src/output-ild.c

        $<$<OR:$<BOOL:${PNG_FOUND}>,$<BOOL:${EMSCRIPTEN}>>:src/input-png.c>

        $<$<BOOL:${ImageMagick_FOUND}>:src/input-magick.c>)

set_target_properties(autotraceLib PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )


if (BUILD_DEPENDENCIES)
    add_dependencies(autotraceLib libpng)
endif ()

target_include_directories(autotraceLib PUBLIC
        ${CMAKE_SOURCE_DIR}
        src)
target_compile_definitions(autotraceLib
        PRIVATE
        $<$<OR:$<BOOL:${PNG_FOUND}>,$<BOOL:${EMSCRIPTEN}>>:HAVE_LIBPNG>
        $<$<BOOL:${ImageMagick_FOUND}>:HAVE_MAGICK>
        PUBLIC
        #  TODO use cmake version
        AUTOTRACE_VERSION="1.0"
        AUTOTRACE_WEB="http://autotrace.sourceforge.net"
        )

add_subdirectory(Vendor)

add_subdirectory(src/wrapper)
if (BUILD_TESTS)
    add_subdirectory(src/test_wrapper)
endif ()

if (EMSCRIPTEN)
    target_compile_options(autotraceLib PUBLIC -s USE_LIBPNG=1)
else ()
    target_link_libraries(autotraceLib PUBLIC
            PNG::PNG
            ${ImageMagick_LIBRARIES})

    target_include_directories(autotraceLib PUBLIC
            ${ImageMagick_INCLUDE_DIRS})

    add_executable(autotrace
            src/atou.c
            src/atou.h
            src/main.c
            src/cmdline.h
            src/strgicmp.h
            )
    target_link_libraries(autotrace PRIVATE autotraceLib m)
endif ()
