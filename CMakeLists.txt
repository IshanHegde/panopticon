cmake_minimum_required(VERSION 3.15)
project(Panopticon)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
# Use POSIX 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_POSIX_C_SOURCE=200809L")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_POSIX_C_SOURCE=200809L -D_GNU_SOURCE")



add_compile_options(-O3 -march=native -mtune=native -flto )

set(LIBRARY_SOURCES src/panopticon.c)

add_library(panopticon ${LIBRARY_SOURCES})


target_include_directories(panopticon PUBLIC src)


add_executable(test_c examples/test_c.c)
target_link_libraries(test_c PRIVATE panopticon)


add_executable(test_cpp examples/test_cpp.cpp)
target_link_libraries(test_cpp PRIVATE panopticon)