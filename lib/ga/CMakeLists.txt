project(gpxtools)

# Define the library sources and headers
set(SOURCES
    exception.cpp
    union.cpp
    image.cpp
    algo.cpp
)

set(HEADERS
    union.h
    ga.h
)

add_library(ga STATIC ${SOURCES} ${HEADERS})