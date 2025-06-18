#include "../../headers/NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(
    std::vector<int> topology,
    std::vector<ActivationType> activations,
    double learningRate) {
    // Saving the topology and computing it's size
    this->topology = topology;
    this->topologySize = topology.size();
    this->learningRate = learningRate;

    if (activations.size() != topologySize) {
        std::cerr << ">>>ERROR: "
        << "Activation size must mathch topology size."
        << std::endl;
    }

    // Creating the layers based on the topology & ActivationTypes
    for (int i = 0; i < topologySize; i++) {
        Layer *l = new Layer(topology[i], activations[i]);
        this->layers.push_back(l);
    }

    // Creating the weight matrix connecting
    // each layer to the next
    for (int i = 0; i < (topologySize - 1); i++) {
        // Matrix dimentions: current layer size * next layer size
        Matrix *weight = new Matrix(topology.at(i), topology.at(i+1), true);
        this->weightMatrices.push_back(weight);
    }
}