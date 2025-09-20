cmake_minimum_required(VERSION 3.31)
project(Lapidary)

add_library(lapidary Lapidary.c)
target_include_directories(lapidary INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(lapidary
	PRIVATE
		Lapidary.h
)
