#include "../../headers/NeuralNetwork.h"

void NeuralNetwork::setCurrentInput(std::vector<double> input) {
    this->input = input;

    for (int i = 0; i < input.size(); i++) {
        this->layers.at(0)->setVal(i, input.at(i));
    }
}

void NeuralNetwork::setCurrentTarget(std::vector<double> target) {
    this->target = target;
}