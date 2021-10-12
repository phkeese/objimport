project(objimport)

cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(libobjimport
	objdata.hpp
	objdata.cpp
	objreader.hpp
	objreader.cpp
	helper_functions.hpp
	objscanner.hpp
	objscanner.cpp
)

add_executable(objimport
	objimport.cpp
)

target_link_libraries(objimport libobjimport)
