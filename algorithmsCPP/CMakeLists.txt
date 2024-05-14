cmake_minimum_required(VERSION 3.5)
project(Sorts VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(SOURCES ./source/main.cpp)
set(HEADERS ./include/sorts.hpp)

add_executable(${PROJECT_NAME}
${SOURCES}
${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ./include)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
