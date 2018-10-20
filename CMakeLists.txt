cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++14")

project(measure)

find_package(OpenCV REQUIRED)

add_executable(
	measure
	src/main.cpp
	src/Measure_Origins.cpp
	src/getExteriorContour.cpp
	src/detectLines.cpp
	include/Measure_Origins.hpp
	include/detectLines.hpp
	include/getExteriorContour.hpp
)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
link_directories( ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

target_link_libraries( measure  ${OpenCV_LIBS} )
