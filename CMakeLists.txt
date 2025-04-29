cmake_minimum_required(VERSION 3.14)
project(prng-bench)

# 1) Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 2) Fetch External Libraries
include(FetchContent)
FetchContent_Declare(
    CLI11
    QUIET
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.5.0
)

FetchContent_MakeAvailable(
    CLI11
)

# 3) Define PRNG Library
add_library(prng
    src/prng/lcg.cpp
    src/prng/mt19937.cpp
    src/prng/pcg32.cpp
    src/prng/split_mix64.cpp    
    src/prng/xor_shift.cpp
)

target_include_directories(prng 
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include/prng
)

# 4) Define Benchmark Library
add_library(benchmark
    src/benchmark/benchmark.cpp
    src/benchmark/benchmark_runner.cpp
)

target_include_directories(benchmark 
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include/benchmark
)

target_link_libraries(benchmark
    PUBLIC
        prng
)

# 5) Define CLI Library
add_library(cli_parser
    src/cli/cli_parser.cpp
)

target_include_directories(cli_parser 
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include/cli
)

target_link_libraries(cli_parser 
    PUBLIC
        CLI11::CLI11
)

# 6) Define the Executable
add_executable(prng-bench src/main.cpp)

# 7) Link Everything
target_link_libraries(prng-bench 
    PRIVATE
        prng
        benchmark
        cli_parser
)
