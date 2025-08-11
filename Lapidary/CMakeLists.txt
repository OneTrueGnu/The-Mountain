cmake_minimum_required(VERSION 4.0.0)
project(Lapidary)

add_library(lapidary Lapidary.c)
target_include_directories(lapidary INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
