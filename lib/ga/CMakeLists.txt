# Define the library sources and headers
set(SOURCES
    exception.cpp
    image.cpp
    pixana.cpp
)

set(HEADERS
    ga.h
)

add_library(ga STATIC ${SOURCES} ${HEADERS})