#pragma once

#include <iostream>
#include <vector>
#include "Neuron.h"
#include "Layer.h"
#include "Matrix.h"

#include "utils/MultiplyMatrix.h"
#include "utils/MatrixToVector.h"


class NeuralNetwork {
public:
    // Constructor
    NeuralNetwork(std::vector<int> topology);

    // Setters
    void setCurrentInput(std::vector<double> input);
    void setCurrentTarget(std::vector<double> target);

    // Well, another setters
    void setNeuronValue(int layerIndex, int neuronIndex, double val) {
        this->layers.at(layerIndex)->setVal(neuronIndex, val);
    }

    void setErrors();

    // printing function
    void printToConsole();

    void feedForward();
    void backPropagation();
    
    // Funcitons to get neuron matrices
    Matrix *getNeuronMatrix(int index) {
        return this->layers.at(index)->matrixifyVals();
    }

    Matrix *getActivatedNeuronMatrix(int index) {
        return this->layers.at(index)->matrixifyActivatedVals();
    }

    Matrix *getDerivedNeuronMatrix(int index) {
        return this->layers.at(index)->matrixifyDerivedVals();
    }

    Matrix *getWeightMatrix(int index)  {
        return this->weightMatrices.at(index);
    }

    double getTotalError() { return this->error; }
    std::vector <double> getErrors() { return this->errors; }

private:
    // Topology represents the number of elements (neurons) in each layer
    std::vector<int> topology;
    int topologySize;
    std::vector<Layer *>    layers;
    std::vector<Matrix *>   weightMatrices;
    std::vector<Matrix *>   gradientMatrices;
    std::vector<double>     input;
    std::vector<double>     target;
    double                  error;
    std::vector<double>     errors;
    std::vector<double>     historicalErrors;
};