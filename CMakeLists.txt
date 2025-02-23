cmake_minimum_required(VERSION 3.27)
project(viterbi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(viterbi
    src/Encoder.cpp
    src/Decoder.cpp
)
target_include_directories(viterbi PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE viterbi)
