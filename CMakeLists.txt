cmake_minimum_required(VERSION 3.8)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

option(BUILD_LIBS_LOCAL "This will pull down any libraries needed and build locally" off)

include(FindPkgConfig)
pkg_check_modules(GLIB glib-2.0 REQUIRED)

find_package(ImageMagick COMPONENTS MagickCore)
find_package(PNG)
# TODO CHECK for SWF
# TODO CHECK for PSTOEDIT

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
        src/output.c
        src/input.c
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

        $<$<BOOL:PNG_FOUND>:src/input-png.c>

        $<$<BOOL:ImageMagick_FOUND>:src/input-magick.c>
        )

target_include_directories(autotraceLib PUBLIC
        ${CMAKE_SOURCE_DIR}
        src
        ${GLIB_INCLUDE_DIRS}
        ${ImageMagick_INCLUDE_DIRS}
        ${PNG_INCLUDE_DIRS})
target_link_libraries(autotraceLib PUBLIC
        ${GLIB_LIBRARIES}
        ${ImageMagick_LIBRARIES}
        ${PNG_LIBRARIES})
target_compile_definitions(autotraceLib
        PRIVATE
        $<$<BOOL:PNG_FOUND>:HAVE_LIBPNG ${PNG_DEFINITIONS}>
        $<$<BOOL:ImageMagick_FOUND>:HAVE_MAGICK>
        PUBLIC
        #  TODO use cmake version
        AUTOTRACE_VERSION="1.0"
        AUTOTRACE_WEB="http://autotrace.sourceforge.net"
        )


add_executable(autotrace
        src/atou.c
        src/atou.h
        src/main.c
        src/cmdline.h
        src/strgicmp.h
        )

target_link_libraries(autotrace PRIVATE autotraceLib m)
