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
)

add_executable(objimport
	main.cpp
)

target_link_libraries(objimport libobjimport)

include(CTest)
enable_testing()

# add_executable(test_scanner tests/test_scanner.cpp)
# target_link_libraries(test_scanner libobjimport)
# add_test(test_all_tokens test_scanner)