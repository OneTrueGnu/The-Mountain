cmake_minimum_required(VERSION 4.0.0)
project(Mountian)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(FetchContent)

FetchContent_Declare(
	SDL
	GIT_REPOSITORY https://github.com/libsdl-org/SDL
	GIT_TAG e699f3dca1c03051a2736cde6fb6d45839f33062 # Roughly version 3.2.20
)
FetchContent_MakeAvailable(SDL)

add_subdirectory(Despicable)
add_subdirectory(Lapidary)
add_subdirectory(Wren)
