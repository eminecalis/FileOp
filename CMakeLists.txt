project(FileOp C)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c11")

set (FILE_OP_FILES main.c)

add_executable(fileop ${FILE_OP_FILES})