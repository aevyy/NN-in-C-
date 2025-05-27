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
    void setVal(int index, double value);

    // A function to convert a vector into 1 by n matrix
    Matrix *matrixifyVals();
    Matrix *matrixifyActivatedVals();
    Matrix *matrixifyDerivedVals();

private:
    int size;   // This is the size of neurons vector
    std::vector<Neuron *> neurons;  // This will contain the instances of Neuron
};