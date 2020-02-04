cmake_minimum_required(VERSION 3.15)
project(BlockEngine)

set(CMAKE_CXX_STANDARD 14)

file (GLOB SOURCES *.cpp)
add_executable(BlockEngine ${SOURCES} glad/glad.c)

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

target_link_libraries(BlockEngine -L${LIB_DIR})
target_link_libraries(BlockEngine libglfw3dll.a)

