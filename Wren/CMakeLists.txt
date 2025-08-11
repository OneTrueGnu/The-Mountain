cmake_minimum_required(VERSION 4.0.0)
project(Wren)

add_library(wren GraphicsObject.c)
target_include_directories(wren INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(wren despicable lapidary)
