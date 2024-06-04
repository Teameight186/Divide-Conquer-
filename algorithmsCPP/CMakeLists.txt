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
    source/algorithms/halfplaneIntersect.cpp
    source/algorithms/kernel.cpp
    source/algorithms/mergeHull.cpp
    source/algorithms/triangulate.cpp
    source/algorithms/voronoiDiagram.cpp
    source/algorithms/closestPoints.cpp
)
set(HEADERS 
    ./include/algorithms/Sorts.hpp
    ./include/geometry/Edge.hpp
    ./include/geometry/Point.hpp
    ./include/geometry/Polygon.hpp
    ./include/geometry/Node.hpp
    ./include/geometry/Vertex.hpp
    ./include/algorithms/halfplaneIntersect.hpp
    ./include/geometry/List.hpp
    ./include/algorithms/kernel.hpp
    ./include/algorithms/mergeHull.hpp
    ./include/algorithms/triangulate.hpp
    ./include/algorithms/voronoiDiagram.hpp
    ./include/algorithms/closestPoints.hpp
)

add_executable(${PROJECT_NAME}
${SOURCES}
${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ./include/geometry ./include/algorithms)
