cmake_minimum_required(VERSION 3.24)
project(tracer)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp shapes/plane.cpp shapes/sphere.cpp shapes/polyhedron.cpp shapes/triangle.cpp shapes/cube.cpp tracer/tracer.cpp scene/scene.cpp color/color.cpp utils/utils.cpp materials/material.cpp)

add_executable(main ${SOURCES})

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_include_directories(main PUBLIC shapes/ tracer/ color/ materials/ scene/ utils/)
target_link_libraries(main sfml-graphics)

install(TARGETS main DESTINATION bin)