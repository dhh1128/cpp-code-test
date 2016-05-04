cmake_minimum_required(VERSION 2.8)

project(check)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SRC_LIST "*.cpp")
file(GLOB HEADERS "*.h")
list(APPEND SRC_LIST ${HEADERS})

add_executable(${PROJECT_NAME} ${SRC_LIST})

