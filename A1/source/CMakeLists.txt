cmake_minimum_required(VERSION 3.17)
project(source)

set(CMAKE_CXX_STANDARD 11)

add_executable(question.a  face2faceindex.cpp)
add_executable(question.b faceindex2directededge.cpp mesh.cpp commonUtilis.h)