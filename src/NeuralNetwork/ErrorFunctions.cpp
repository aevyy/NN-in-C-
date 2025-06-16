#include "../../headers/NeuralNetwork.h"

void NeuralNetwork::setErrors() {
    if (this->target.size() != this->layers.at(this->layers.size() - 1)->getNeurons().size()) {
    std::cerr << ">>> DEBUG: target size = " << this->target.size()
              << ", output layer size = "
              << this->layers.at(this->layers.size() - 1)->getNeurons().size()
              << std::endl;
    std::cerr << "Target size is not same as output layer size." << std::endl;
    assert(false);
}


    // The target size should be the same size as the output layer
    if (this->target.size() != this->layers.at(this->layers.size() - 1)->getNeurons().size()) {
        std::cerr << "Target size is not same at the output layer size: "
        << this->layers.at(this->layers.size() - 1)->getNeurons().size() << std::endl;
        assert(false);
    }

    this->error = 0.00;
    int outputLayerIndex = this->layers.size() - 1;
    std::vector<Neuron *> outputNeurons = this->layers.at(outputLayerIndex)->getNeurons();

    // I am resizing the errors before filing to prevent errors
    this->errors.resize(target.size());
    
    for (int i = 0; i < target.size(); i++) {
        // Previous cost function:s
        // double tempErr = (outputNeurons.at(i) ->getActivatedVal() - target.at(i));

        // Updated cost function:
        // Computes the squared error between target and prediction
        double tempErr = outputNeurons.at(i)->getActivatedVal() - target.at(i);
        errors.at(i) = tempErr;
        this->error += pow(tempErr, 2);
    }
    // Final cost: one half of sum of squared errors (standard quadratic cost)
    this->error = 0.5 * this->error;

    // Keeping track of all the errors on each iteration
    historicalErrors.push_back(this->error);
}