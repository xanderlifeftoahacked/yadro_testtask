cmake_minimum_required(VERSION 3.27)
project(viterbi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_library(viterbi
    src/Encoder.cpp
    src/Decoder.cpp
		src/Channel.cpp
)

find_package(Boost REQUIRED COMPONENTS iostreams system filesystem)

include_directories(
	"${Boost_INCLUDE_DIRS}"
)

target_include_directories(viterbi PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/lib/gnuplot-iostream"
)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE viterbi ${Boost_LIBRARIES})
