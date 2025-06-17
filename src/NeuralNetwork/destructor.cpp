#include "../../headers/NeuralNetwork.h"

NeuralNetwork::~NeuralNetwork() {
    // Cleaning layers
    for (Layer* layer : this->layers) {
        delete layer;
    }

    // Cleaning weights
    for (Matrix *weight : this->weightMatrices) {
        delete weight;
    }

    // Cleaning gradients
    for (Matrix *gradient : this->gradientMatrices) {
        delete gradient;
    }
}