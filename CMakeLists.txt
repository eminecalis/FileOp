project(FileOp C)
cmake_minimum_required(VERSION 3.5.1)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c11")

find_package(PkgConfig)

pkg_check_modules (GLIB REQUIRED glib-2.0)

# this is useful for debugging, just use "message()" to print something
if (GLIB_FOUND)
    message(${GLIB_INCLUDE_DIRS})
endif()

include_directories(${GLIB_INCLUDE_DIRS}) # -I

link_libraries(${GLIB_LIBRARIES}) # -l

link_directories(${}) # -L

set (FILE_OP_FILES main.c list.c list.h)

add_executable(fileop ${FILE_OP_FILES})
