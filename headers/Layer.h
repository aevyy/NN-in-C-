#pragma once

#include <iostream>
#include <vector>
#include "Neuron.h"
#include "Matrix.h"

class Layer {
public:
    // Constructor
    Layer(int size);
    Layer(int size, ActivationType activationType);

    // Destrictor
    ~Layer();

    // Delete copy constructor and assignment to prevent shallow copies
    Layer(const Layer&) = delete;
    Layer& operator=(const Layer&) = delete;

    // Mutators and Accessors
    void setVal(int index, double val);
    void setNeuron(std::vector<Neuron*>& neurons);
    std::vector<Neuron *> getNeurons() const { return neurons; }

    std::vector<double> getActivatedVals() const;

    // Matrix representations of neuron values
    Matrix matrixifyVals() const;
    Matrix matrixifyActivatedVals() const;
    Matrix matrixifyDerivedVals() const;

private:
    // Number of neurons in the layer
    int size;
    // The instances of Neuron
    std::vector<Neuron*> neurons;
};