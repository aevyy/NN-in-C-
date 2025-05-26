#pragma once

#include <iostream>
#include <vector>
#include "Neuron.h"
#include "Layer.h"
#include "Matrix.h"

class NeuralNetwork {
public:
    // Constructor
    NeuralNetwork(std::vector<int> topology);

private:
    // Topology represents the number of elements (neurons) in each layer
    std::vector<int> topology;
    std::vector<Layer *> layers;
    std::vector<Matrix *> weightMetrices;
};