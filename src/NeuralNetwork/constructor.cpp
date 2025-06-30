#include <fstream>
#include "../../headers/NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(
        std::vector<int> topology,
        double bias,
        double learningRate,
        double momentum
    ) {

    // Saving the topology and computing it's size
    this->topology      = topology;
    this->topologySize  = topology.size();
    this->learningRate  = learningRate;
    this->momentum      = momentum;
    this->bias          = bias;

    // Creating the layers
    for (int i = 0; i < topologySize; i++) {
        Layer *l;

        if (i > 0 && i < (topologySize - 1)) {
            l = new Layer(topology.at(i), this->hiddenActivationType);
        } 
        else if (i == (topologySize - 1)) {
            l = new Layer(topology.at(i), this->outputActivationType);
        } 
        else {        // Input layer
            l = new Layer(topology.at(i));
        }
        
        this->layers.push_back(l);
    }

    // Creating the weight matrices between each pair of layers with proper initialization
    for (int i = 0; i < (topologySize - 1); i++) {
        // Matrix dimensions: current layer size * next layer size
        int inputSize = topology.at(i);      // Previous layer neurons
        int outputSize = topology.at(i+1);   // Current layer neurons
        
        // creating an empty matrix
        Matrix *weight = new Matrix(inputSize, outputSize, false);
        
        // He initialization default
        weight->initializeHe(inputSize);
        
        this->weightMatrices.push_back(weight);
    }

    // Setting initial errors
    for (int i = 0; i < (topology.at(topologySize - 1)); i++) {
        this->errors.push_back(0.00);
    }

    this->error = 0.00;
}


NeuralNetwork::NeuralNetwork (
        std::vector<int> topology,
        ActivationType hiddenActivationType,
        ActivationType outputActivationType,
        int costFunctionType,
        double bias,
        double learningRate,
        double momentum
    ) {
    
    this->topology      = topology;
    this->topologySize  = topology.size();
    this->learningRate  = learningRate;
    this->momentum      = momentum;
    this->bias          = bias;

    this->hiddenActivationType  = hiddenActivationType;
    this->outputActivationType  = outputActivationType;
    this->costFunctionType      = costFunctionType;

    // Creating the layers
    for (int i = 0; i < topologySize; i++) {
        Layer *l;

        if (i > 0 && i < (topologySize - 1)) {
            l = new Layer(topology.at(i), this->hiddenActivationType);
        } 
        else if (i == (topologySize - 1)) {
            l = new Layer(topology.at(i), this->outputActivationType);
        } 
        else {        // Input layer
            l = new Layer(topology.at(i));
        }
        
        this->layers.push_back(l);
    }

    // Creating the weight matrices between each pair of layers with SMART initialization
    for (int i = 0; i < (topologySize - 1); i++) {
        // Matrix dimensions: current layer size * next layer size
        int inputSize = topology.at(i);      // Previous layer neurons
        int outputSize = topology.at(i+1);   // Current layer neurons
        
        // Creating an empty matrix
        Matrix *weight = new Matrix(inputSize, outputSize, false);
        
        // Initialization based on layer type and activation function
        if (i == (topologySize - 2)) {
            // OUTPUT LAYER: Xavier initialization (works great with Sigmoid)
            weight->initializeXavier(inputSize, outputSize);
        } else {
            // HIDDEN LAYERS
            if (this->hiddenActivationType == RELU) {
                // ReLU activation: He initialization
                weight->initializeHe(inputSize);
            } else {
                // Sigmoid/Tanh activation: Xavier initialization
                weight->initializeXavier(inputSize, outputSize);
            }
        }
        
        this->weightMatrices.push_back(weight);
    }

    // Setting initial errors
    for (int i = 0; i < (topology.at(topologySize - 1)); i++) {
        this->errors.push_back(0.00);
    }

    this->error = 0.00;
            
}