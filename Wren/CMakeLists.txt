cmake_minimum_required(VERSION 4.0.0)
project(Wren)

add_subdirectory(vendored/glad)
add_subdirectory(vendored/stb_image)

add_library(wren textured_quad.c texture_loading.c shader_loading.c)
target_include_directories(wren INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(wren despicable lapidary glad stb_image)
