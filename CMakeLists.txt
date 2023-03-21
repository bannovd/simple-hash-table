cmake_minimum_required(VERSION 3.5)

project(simple-hash-table LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(simple-hash-table src/main.cpp
    src/hashtable.h src/hashtable.cpp)

install(TARGETS simple-hash-table
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
