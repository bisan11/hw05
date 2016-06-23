cmake_minimum_required(VERSION 3.5)
project(CHW05_refactored)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -Wall -Wextra -pedantic")

set(SOURCE_FILES
    dataStructure.c
    dataStructure.h
    fileInfo.c
    fileInfo.h
    options.c
    options.h
    posixFuncs.c
    posixFuncs.h
    program.c)

add_executable(CHW05_refactored ${SOURCE_FILES})