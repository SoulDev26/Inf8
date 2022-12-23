cmake_minimum_required(VERSION 3.10)

project(inf8 LANGUAGES C)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
add_executable(inf8 inf8.c ${SOURCES})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(inf8 SDL2 SDL2_ttf)