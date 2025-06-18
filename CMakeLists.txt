cmake_minimum_required(VERSION 3.15)
project(main)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collecting all source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

# Including directories for headers
include_directories(
    headers
    headers/Matrix
    headers/Neuron
    headers/Layer
    headers/NeuralNetwork
    headers/utils/DataLoader
    
)

# The executable
add_executable(${PROJECT_NAME} ${SOURCES})
