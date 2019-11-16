cmake_minimum_required(VERSION 3.2)

cmake_policy(SET CMP0048 NEW)
project(autotrace)

find_package(ImageMagick COMPONENTS MagickCore)
find_package(PNG)
## TODO CHECK for SWF
## TODO CHECK for PSTOEDIT

set(LIB_SRCS
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
  $<$<BOOL:${PNG_FOUND}>:src/input-png.c>
  $<$<BOOL:${ImageMagick_FOUND}>:src/input-magick.c>
  )

add_library(libautotrace ${LIB_SRCS})
set_target_properties(libautotrace PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  PREFIX ""
  )

if (TARGET libpng)
  add_dependencies(libautotrace libpng)
endif ()

target_include_directories(libautotrace PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  )
target_compile_definitions(libautotrace
  PRIVATE
  $<$<BOOL:${PNG_FOUND}>:HAVE_LIBPNG>
  $<$<BOOL:${ImageMagick_FOUND}>:HAVE_MAGICK>
  PUBLIC
  #  TODO use cmake version
  AUTOTRACE_VERSION="1.0"
  AUTOTRACE_WEB="http://autotrace.sourceforge.net"
  )

add_subdirectory(Vendor)

target_link_libraries(libautotrace PUBLIC
  PNG::PNG
  ${ImageMagick_LIBRARIES})

target_include_directories(libautotrace PUBLIC
  ${ImageMagick_INCLUDE_DIRS})

add_executable(autotrace
  src/atou.c
  src/atou.h
  src/main.c
  src/cmdline.h
  )
target_link_libraries(autotrace PRIVATE libautotrace m)

enable_testing()
add_subdirectory(tests)

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8
