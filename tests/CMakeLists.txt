cmake_minimum_required(VERSION 3.28)
project(centests LANGUAGES CXX)

add_executable(testzero testzero.cpp)
add_executable (test1 test1.cpp)
add_executable (example example.cpp)

target_link_libraries(testzero PRIVATE cenui)
target_link_libraries(test1 PRIVATE cenui)
target_link_libraries(example PRIVATE cenui)