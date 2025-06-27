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

    switch(costFunctionType) {
        case COST_MSE: this->setErrorMSE(); break;
        default: this->setErrorMSE(); break;
    }
}

void NeuralNetwork::setErrorMSE() {
    int outputLayerIndex = this->layers.size() - 1;
    std::vector<Neuron *> outputNeurons = this->layers.at(outputLayerIndex)->getNeurons();
    int outputLayerSize = outputNeurons.size();

    this->error = 0.00;

    // Resetting error vectors
    this->errors.clear();
    this->derivedErrors.clear();
    this->errors.resize(outputLayerSize, 0.0);
    this->derivedErrors.resize(outputLayerSize, 0.0);

    for (int i = 0; i < this->target.size(); i++) {
        double target = this->target.at(i);
        double prediction = outputNeurons.at(i)->getActivatedVal();

        double diff = prediction - target;
        errors.at(i) = diff * diff;         // Squared error (always positive)
        derivedErrors.at(i) = 2.0 * diff;   // Proper MSE derivative: 2(pred - target)
        this->error += errors.at(i);
    }

    this->error *= 0.5;

    this->historicalErrors.push_back(this->error);
}