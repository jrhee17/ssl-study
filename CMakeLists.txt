cmake_minimum_required(VERSION 3.5)
project(dummy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES "./before/**/*")
#set(SOURCE_FILES "./before/ch01/base64.c" "./before/ch01/base64.h" "./before/ch01/http.c" "./before/ch01/webserver.c")
add_executable(dummy ${SOURCE_FILES})
