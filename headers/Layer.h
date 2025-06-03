#pragma once

#include <iostream>
#include <vector>
#include "Neuron.h"
#include "Matrix.h"

class Layer {
public:
    // Constructor
    Layer(int size);

    // setter
    void setVal(int index, double val);
    void setNeuron(std::vector<Neuron *> neurons) { this->neurons = neurons; }


    // A function to convert a vector into 1 by n matrix
    Matrix *matrixifyVals();
    Matrix *matrixifyActivatedVals();
    Matrix *matrixifyDerivedVals();

    // Getters
    std::vector<Neuron *> getNeurons() { return this->neurons; }

private:
    int size;   // This is the size of neurons vector
    std::vector<Neuron *> neurons;  // This will contain the instances of Neuron
};