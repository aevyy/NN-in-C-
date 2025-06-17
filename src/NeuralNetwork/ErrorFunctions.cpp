#include "../../headers/NeuralNetwork.h"

void NeuralNetwork::setErrors() {
    // Output layer information
    int outputLayerIndex    = this->layers.size() - 1;
    int outputLayerSize     = this->layers[outputLayerIndex]->getNeurons().size();

    // Check target size matches output layer size
    if (this->target.size() != outputLayerSize) {
    std::cerr   << ">>> ERROR: target size = " << this->target.size()
                << ", output layer size = " << outputLayerSize << std::endl
                << "Target size is not same as output layer size." << std::endl;

                return;     // Cannot proceed with invalid state
    }

    // Reset error tracking
    this->error = 0.00;
    this->errors.clear();
    this->errors.reserve(outputLayerSize);  // Pre-allocating memory

    // Getting output neurons
    std::vector<Neuron *> outputNeurons = this->layers[outputLayerIndex]->getNeurons();

    // Calculaating errors    
    for (int i = 0; i < target.size(); i++) {
        // Previous cost function:
        // double tempErr = (outputNeurons.at(i) ->getActivatedVal() - target.at(i));

        // Updated cost function:
        // Computes the squared error between target and prediction
        double output   = outputNeurons.at(i)->getActivatedVal();
        double tempErr  = output - target.at(i);
        this->error     += tempErr * tempErr; // Sum of squared errors

        this->errors.push_back(tempErr);

    }
    // Final cost: one half of sum of squared errors (quadratic cost)
    this->error = 0.5 * this->error;

    // Keeping track of all the errors on each iteration
    this->historicalErrors.push_back(this->error);
}