project(gpxtools)

# google test
set (GA_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ga"
    CACHE PATH "Path to the graph algorithms library")
add_subdirectory(ga)

# google test
set (GTEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest"
    CACHE PATH "Path to googletest library")
add_subdirectory(googletest)