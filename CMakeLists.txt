cmake_minimum_required(VERSION 3.14)
project(prng-bench)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
	${PROJECT_SOURCE_DIR}/include
)

# Enable visualization
option(ENABLE_VISUALIZATION "Enable Matplot++ plotting" OFF)

# Define the prng lib
add_library(prng INTERFACE)
target_include_directories(prng INTERFACE
	${PROJECT_SOURCE_DIR}/include/prng
)

# Define the seeder lib
add_library(seeder INTERFACE)
target_include_directories(seeder INTERFACE
	${PROJECT_SOURCE_DIR}/include/seeder
)

# Define the benchmark lib
add_library(benchmark INTERFACE)
target_include_directories(benchmark INTERFACE
	${PROJECT_SOURCE_DIR}/include/benchmark
)

# Visualization (Conditional)
if(ENABLE_VISUALIZATION)
	add_library(visualization INTERFACE)
	target_include_directories(visualization INTERFACE
		${PROJECT_SOURCE_DIR}/include/visualization
	)
endif()

# Executable
add_executable(prng-bench src/main.cpp)

# Link against libs
target_link_libraries(prng-bench
	prng
	seeder
	benchmark
	visualization
)
