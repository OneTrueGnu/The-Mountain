cmake_minimum_required(VERSION 3.31)
project(Wren)

add_library(stb_image stb_image_implementation.c)
target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
