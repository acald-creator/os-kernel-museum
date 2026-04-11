cmake_minimum_required(VERSION 3.13)
project(libc LANGUAGES C CXX ASM)
set(CMAKE_CXX_STANDARD 17)

add_library(libc STATIC "")
target_sources(libc PRIVATE
        src/fs/fs.c
        )

set_target_properties(libc PROPERTIES PUBLIC_HEADER include/sys/cdefs.h)
include(GNUInstallDirs)
install(TARGETS libc
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
