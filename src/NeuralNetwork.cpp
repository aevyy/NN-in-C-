#include "../headers/NeuralNetwork.h"

void NeuralNetwork::setCurrentInput(std::vector<double> input) {
    this->input = input;
}

// Constructor for NeuralNetwork class
NeuralNetwork::NeuralNetwork(std::vector<int> topology) {
    // Saving the topology and computing it's size
    this->topology = topology;
    this->topologySize = topology.size();

    // Creating the layers based on the topology
    for (int i = 0; i < topologySize; i++) {
        Layer *l = new Layer(topology.at(i));
        this->layers.push_back(l);
    }

    // Creating the weight matrix connecting
    // each layer to the next
    for (int i = 0; i < (topologySize - 1); i++) {
        // Matrix dimentions: current layer size * next layer size
        Matrix *m = new Matrix(topology.at(i), topology.at(i+1), true);
        this->weightMetrices.push_back(m);
    }
}