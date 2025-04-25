cmake_minimum_required(VERSION 3.14)
project(prng-bench)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define executable
add_executable(prng-bench src/main.cpp)

target_link_libraries(prng-bench
    prng
)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# Define prng library
add_library(prng
    src/prng/lcg.cpp
    src/prng/mt19937.cpp
)

target_include_directories(prng PUBLIC
    ${CMAKE_SOURCE_DIR}/include/prng
)

# Define benchmark library
target_include_directories(prng-bench PUBLIC
    ${CMAKE_SOURCE_DIR}/include/benchmark
)
