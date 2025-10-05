cmake_minimum_required(VERSION 3.31)
project(Despicable)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_C_STANDARD 99)

add_library(despicable 2DVector.c minmax.c rectangles.c)
target_include_directories(despicable INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(despicable lapidary)
target_sources(despicable
	PRIVATE
		Despicable.h
)
