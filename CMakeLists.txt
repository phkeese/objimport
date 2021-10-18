project(objimport)

cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(libobjimport
	objdata.hpp
	objdata.cpp
	objparser.hpp
	objparser.cpp
	parser.hpp
	parser.cpp
	mtldata.hpp
	mtldata.cpp
	mtlparser.hpp
	mtlparser.cpp
)

add_executable(objimport
	main.cpp
)

target_link_libraries(objimport libobjimport)

include(CTest)
enable_testing()

# This is where I would put my tests... if I had any