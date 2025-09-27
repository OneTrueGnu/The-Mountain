cmake_minimum_required(VERSION 3.31)
project(Despicable)

add_library(despicable 2DVector.c minmax.c rectangles.c fast_inv_sqrt.c)
target_include_directories(despicable INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(despicable lapidary)
target_sources(despicable
	PRIVATE
		Despicable.h
)
