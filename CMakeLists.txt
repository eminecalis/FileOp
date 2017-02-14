project(FileOp C)
cmake_minimum_required(VERSION 3.5.1)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c11 -Wall")

find_package(PkgConfig)

pkg_check_modules (GLIB REQUIRED glib-2.0)

# this is useful for debugging, just use "message()" to print something
if (GLIB_FOUND)
    message(${GLIB_INCLUDE_DIRS})
endif()

include_directories(${GLIB_INCLUDE_DIRS}) # -I

link_libraries(${GLIB_LIBRARIES}) # -l

# this is not strictly necessary for glib because the compiled library is
# installed into a standard path that gcc can find by default
link_directories(${GLIB_LIBRARY_DIRS}) # -L

set (FILE_OP_FILES main.c list.c list.h)
set (GLIB_FILES glib-practice/main.c)

add_executable(fileop ${FILE_OP_FILES})
add_executable(glibpractice ${GLIB_FILES})

set (CONTACT_GENERATOR_CLIENT
        contact-generator/contact-client.c
        contact-generator/contact-client.h)

add_executable(contact-client ${CONTACT_GENERATOR_CLIENT})
