cmake_minimum_required(VERSION 3.28)
project(centests LANGUAGES CXX)

add_executable(testzero testzero.cpp)

target_link_libraries(testzero PRIVATE cenui)