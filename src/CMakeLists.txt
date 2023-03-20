add_executable(vectorize vectorize/vectorize.cpp)
target_link_libraries(vectorize ga)

add_executable(snatch snatch/snatch.cpp)
target_link_libraries(snatch ga)