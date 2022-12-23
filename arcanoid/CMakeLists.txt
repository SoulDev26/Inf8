cmake_minimum_required(VERSION 3.10)

project(arcanoid LANGUAGES C)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")

add_library(arcanoid SHARED arcanoid.c ${SOURCES})

#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)