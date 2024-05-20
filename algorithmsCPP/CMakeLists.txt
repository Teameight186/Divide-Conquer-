cmake_minimum_required(VERSION 3.5)
project(Sorts VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(SOURCES 
    source/main.cpp
    source/geometry/Edge.cpp
    source/geometry/Point.cpp
    source/geometry/Node.cpp
    source/geometry/Vertex.cpp
    source/geometry/Polygon.cpp
)
set(HEADERS 
    ./include/algorithms/sorts.hpp
    ./include/geometry/Edge.hpp
    ./include/geometry/Point.hpp
    ./include/geometry/Polygon.hpp
    ./include/geometry/Node.hpp
    ./include/geometry/Vertex.hpp
)

add_executable(${PROJECT_NAME}
${SOURCES}
${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ./include/geometry ./include/algorithms)
