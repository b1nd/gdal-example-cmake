cmake_minimum_required(VERSION 3.8)
project(gdal_example_cmake)

set(CMAKE_CXX_STANDARD 17)

include(cmake/Core.cmake)

find_package(GDAL REQUIRED)
find_library(GDAL_LIB_FILE GDAL)
get_filename_component(GDAL_LIB ${GDAL_LIB_FILE} DIRECTORY)
get_filename_component(INSTALLED_LIBS ${GDAL_LIB} DIRECTORY)
include_directories(${INSTALLED_LIBS}/include/)

single_executable(src/attributes.cpp)
single_executable(src/polygon_points.cpp)
single_executable(src/topology.cpp)
single_executable_link_libraries(src/attributes.cpp ${GDAL_LIBRARIES})
single_executable_link_libraries(src/polygon_points.cpp ${GDAL_LIBRARIES})
single_executable_link_libraries(src/topology.cpp ${GDAL_LIBRARIES})