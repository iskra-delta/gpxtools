cmake_minimum_required(VERSION 3.2)

set (CMAKE_CXX_STANDARD 20)

project(gpxtools    VERSION 1.0
                    DESCRIPTION "libgpx tools."
                    LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin/)
set(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin/)

include_directories(lib)
include_directories(src)

add_subdirectory(lib/ga)
add_subdirectory(src)