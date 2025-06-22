#pragma once

#include <iostream>
#include <vector>
#include <algorithm> // just to use std::reverse().
#include "Neuron.h"
#include "Layer.h"
#include "Matrix.h"

#define COST_MSE = 1;

class NeuralNetwork {
public:
    // Constructors
    NeuralNetwork(
        std::vector<int> topology,
        double bias = 1,
        double learningRate = 0.05,
        double momentum = 1
    );

    NeuralNetwork (
        std::vector<int> topology,
        ActivationType hiddenActivationType,
        ActivationType outputActivationType,
        int costFunctionType,
        double bias = 1,
        double learningRate = 0.05,
        double momentum = 1
    );

    ~NeuralNetwork();

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
    Matrix getNeuronMatrix(int index) {
        return layers.at(index)->matrixifyVals();
    }

    Matrix getActivatedNeuronMatrix(int index) {
        return layers.at(index)->matrixifyActivatedVals();
    }

    Matrix getDerivedNeuronMatrix(int index) {
        return layers.at(index)->matrixifyDerivedVals();
    }

    Matrix* getWeightMatrix(int index)  {
        return weightMatrices.at(index);
    }

    double getTotalError() { return this->error; }
    std::vector <double> getErrors() { return this->errors; }

    // More print functions for testing
    void printInputToConsole();
    void printOutputToConsole();
    void printTargetToConsole();
    void printHistoricalErrors();

    // Public data
    int topologySize;
    int costFunctionType COST_MSE;

    ActivationType hiddenActivationType = RELU;
    ActivationType outputActivationType = SIGM;

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
    double                  learningRate;
    double                  bias;
    double                  momentum;
};