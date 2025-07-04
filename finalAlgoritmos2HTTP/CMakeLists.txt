cmake_minimum_required(VERSION 3.14)

project(FinalAlgoritmos2)   

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.h include/*.hpp)

add_executable(MainProgram main.cpp ${SRC_FILES} ${HEADER_FILES})
