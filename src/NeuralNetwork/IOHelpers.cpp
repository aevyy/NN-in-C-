#include "../../headers/NeuralNetwork.h"

void NeuralNetwork::printInputToConsole() {
    for (int i = 0; i < this->input.size(); i++) {
        std::cout << this->input.at(i) << "\t";
    }
    std::cout << std::endl;
}

void NeuralNetwork::printTargetToConsole() {
    for (int i = 0; i < this->target.size(); i++) {
        std::cout << this->target.at(i) << "\t";
    }
    std::cout << std::endl;
}

void NeuralNetwork::printHistoricalErrors() {
    for (int i = 0; i < this->historicalErrors.size(); i++) {
        std::cout << this->historicalErrors.at(i);
        if (i != this->historicalErrors.size()-1) {
            std::cout << ",";
        }
    }
    std::cout << std::endl;
}

void NeuralNetwork::printOutputToConsole() {
    int outputLayerIndex    = this->layers.size() - 1;
    Matrix *outputValues    = this->layers.at(outputLayerIndex)->matrixifyActivatedVals();
    for (int c = 0; c < outputValues->getNumCols(); c++) {
         std::cout << outputValues->getValue(0, c) << "\t";
    }
}

void NeuralNetwork::printToConsole() {
    for (int i = 0; i < this->layers.size(); i++) {

        std::cout << "LAYER: " << i << std::endl;

        if (i == 0) {
            Matrix *m = this->layers.at(i)->matrixifyVals();
            m->printToConsole();
        } else {
            Matrix *m = this->layers.at(i)->matrixifyActivatedVals();
            m->printToConsole();
        }

        std::cout << "=========================\n";
        if (i < this->layers.size()-1) {
            std::cout << "Weight Matrix: " << i << std::endl;
            this->getWeightMatrix(i)->printToConsole();
        }
        std::cout << "=========================\n";
    }
}