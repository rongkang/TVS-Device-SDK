cmake_minimum_required(VERSION 2.8)
project(sample_voice)
include_directories(../../include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../out/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../out/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../out/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -fexceptions -fpermissive -fPIC")

# 编译测试文件
add_executable(${PROJECT_NAME} testvoice.cpp)
target_link_libraries(${PROJECT_NAME} -L../../libs  taisdk  -pthread )


