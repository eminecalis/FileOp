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
set (CONTACT_GENERATOR_SAMPLE_FILES
        contact-generator-sample/contact-generator.c
        contact-generator-sample/contact-generator.h
        contact-generator-sample/contact.h contact-generator-sample/protocol.h)
set (CONTACT_GENERATOR_SAMPLE_CLIENT_FILES
        contact-generator-sample/contact-client.c
        contact-generator-sample/contact-client.h
        contact-generator-sample/protocol.h)

add_executable(fileop ${FILE_OP_FILES})
add_executable(glibpractice ${GLIB_FILES})

add_executable(contact-generator-sample ${CONTACT_GENERATOR_SAMPLE_FILES})
add_executable(contact-client-sample ${CONTACT_GENERATOR_SAMPLE_CLIENT_FILES})

set (CONTACT_GENERATOR_CLIENT
        contact-generator/contact-client.c
        contact-generator/contact-client.h)

add_executable(contact-client ${CONTACT_GENERATOR_CLIENT})

set (SORT_WITH_EXEC_FILES
        sorting-with-exec/sort-with-exec.c
        sorting-with-exec/sort-with-exec.h)

add_executable(sorting-with-exec ${SORT_WITH_EXEC_FILES})

set(CONTACT_CLIENT_FILES contact-manager/contact-client.c
                        contact-manager/contact-client.h
                        contact-manager/contact.h)

set(CONTACT_GENERATOR_FILES contact-manager/contact-generator.c
                     contact-manager/contact-generator.h
                     contact-manager/contact.h)

add_executable(contact-manager-client ${CONTACT_CLIENT_FILES})

add_executable(contact-manager-generator ${CONTACT_GENERATOR_FILES})

