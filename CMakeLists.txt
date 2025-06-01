cmake_minimum_required(VERSION 3.10)
project(NeuralNetworkCPP)

# Using C++17
set(CMAKE_CXX_STANDARD 17)

# The header files directory
include_directories(headers)

# The source files
set(SOURCES
    src/main.cpp
    src/Neuron.cpp
    src/Matrix.cpp
    src/Layer.cpp
    src/NeuralNetwork.cpp
    src/utils/MatrixToVector.cpp
    src/utils/MultiplyMatrix.cpp
)

# Defining the executable
add_executable(main ${SOURCES})
