cmake_minimum_required(VERSION 3.10)
project(NeuralNetworkCPP)

# Use C++17
set(CMAKE_CXX_STANDARD 17)

# Include the header files directory
include_directories(headers)

# Set the source files
set(SOURCES
    src/main.cpp
    src/Neuron.cpp
    src/Matrix.cpp
    src/Layer.cpp
    src/NeuralNetwork.cpp
)

# Define the executable
add_executable(main ${SOURCES})
