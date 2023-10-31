project(gpxtools)

# Include files.
include_directories(${GTEST_PATH}/include)

# Test executable.
add_executable(tests main.cpp test-blob.cpp)

# Link in google tests.
target_link_libraries(tests gtest gtest_main)