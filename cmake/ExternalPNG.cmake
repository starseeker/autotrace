# Build a local version of zlib and libpng
INCLUDE(ExternalProject)

SET(libpng_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/libpng)

SET(libpng_CMAKE_ARGS
        -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
        -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
        -DPNG_SHARED=OFF
        -DBUILD_SHARED_LIBS=FALSE
        -DSKIP_INSTALL_FILES=1
        )

EXTERNALPROJECT_ADD(zlib
        PREFIX ${libpng_PREFIX}

        URL http://zlib.net/zlib-1.2.11.tar.gz
        URL_MD5 1c9f62f0778697a09d36121ead88e08e

        PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/cmake/zlib.cmake <SOURCE_DIR>/CMakeLists.txt && ${CMAKE_COMMAND} -E remove <SOURCE_DIR>/zconf.h

        INSTALL_DIR ${CMAKE_BINARY_DIR}/external
        CMAKE_ARGS ${libpng_CMAKE_ARGS}
        )

EXTERNALPROJECT_ADD(libpng
        DEPENDS zlib
        PREFIX ${libpng_PREFIX}

        URL ftp://ftp.simplesystems.org/pub/libpng/png/src/history/libpng15/libpng-1.5.10.tar.gz
        URL_MD5 9e5d864bce8f06751bbd99962ecf4aad

        INSTALL_DIR ${CMAKE_BINARY_DIR}/external
        CMAKE_ARGS ${libpng_CMAKE_ARGS} -DCMAKE_PREFIX_PATH=${CMAKE_BINARY_DIR}/external # to find zlib
        )
