cmake_minimum_required(VERSION 3.20)
project(dismat1_1_ C)

set(CMAKE_C_STANDARD 11)

add_executable(dismat1_1_ main.c)

add_subdirectory(libs)

target_link_libraries(dismat1_1_ bitset)
