cmake_minimum_required(VERSION 3.7)
project(flightRecurl)

if(WINDOWS_BUILD)
	message(STATUS "Cross compiling: Unix->Windows")
	set(CMAKE_C_COMPILER  x86_64-w64-mingw32-gcc)
	set(CMAKE_CXX_COMPILER  x86_64-w64-mingw32-g++)

	set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
	set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
	set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endif()

set(CMAKE_C_FLAGS "-O2")
set(CMAKE_CXX_FLAGS "-O2")
if(RELEASE)
	message(STATUS "Stripping symbols and debug info")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s")
else()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()
set(MOD_NAME flightRecurl CACHE STRING "Used as root directory for mod source + logic file name")

add_library(flightRecurl SHARED
	GameAPI/C/GameAPI/Game.c
	${MOD_NAME}/dllmain.c
	${MOD_NAME}/All.c
)

target_include_directories(flightRecurl PRIVATE
	${MOD_NAME}/
	${MOD_NAME}/Global/
	GameAPI/C/
)

set_target_properties(flightRecurl PROPERTIES OUTPUT_NAME ${MOD_NAME})
target_compile_definitions(flightRecurl PRIVATE RETRO_REVISION=${RETRO_REVISION})

if(WINDOWS_BUILD)
	set_target_properties(flightRecurl PROPERTIES SUFFIX ".dll")
endif()

unset(MOD_NAME CACHE)
