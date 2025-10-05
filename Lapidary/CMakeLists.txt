cmake_minimum_required(VERSION 3.31)
project(Lapidary)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_C_STANDARD 99)

add_library(lapidary Lapidary.c)
target_include_directories(lapidary INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(lapidary
	PRIVATE
		Lapidary.h
)
