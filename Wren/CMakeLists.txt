cmake_minimum_required(VERSION 3.31)
project(Wren)

add_subdirectory(vendored/stb_image)
add_subdirectory(vendored/glad)

add_library(wren textured_quad.c texture_loading.c shader_loading.c)
target_include_directories(wren INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(wren lapidary glad stb_image)
target_sources(wren
	PRIVATE
		Wren.h
)
