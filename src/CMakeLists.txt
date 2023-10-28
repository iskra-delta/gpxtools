project(gpxtools)

set(CMAKE_BUILD_TYPE "Debug")

add_executable(vectorize vectorize/vectorize.cpp)

target_link_libraries(vectorize ga)