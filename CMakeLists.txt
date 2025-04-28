cmake_minimum_required(VERSION 3.14)
project(prng-bench)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define executable
add_executable(prng-bench src/main.cpp)

# External libraries
include(FetchContent)

FetchContent_Declare(
    cli11_proj
    QUIET
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.5.0
)

FetchContent_MakeAvailable(
    cli11_proj
)

# Include directories for project headers
target_include_directories(prng-bench PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    CLI11::CLI11
)

# Link libraries
target_link_libraries(prng-bench
    prng
    benchmark
)

# Define prng library
add_library(prng
    src/prng/lcg.cpp
    src/prng/mt19937.cpp
    src/prng/pcg32.cpp
    src/prng/split_mix64.cpp
    src/prng/xor_shift.cpp
)

target_include_directories(prng PUBLIC
    ${CMAKE_SOURCE_DIR}/include/prng
)

# Define benchmark library
add_library(benchmark
    src/benchmark/benchmark.cpp
    src/benchmark/benchmark_runner.cpp
)

target_include_directories(benchmark PUBLIC
    ${CMAKE_SOURCE_DIR}/include/benchmark
    ${CMAKE_SOURCE_DIR}/include/prng
)
