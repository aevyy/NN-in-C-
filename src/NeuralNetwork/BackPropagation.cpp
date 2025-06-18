#include "../../headers/NeuralNetwork.h"

void NeuralNetwork::backPropagation() {
    std::vector <Matrix *> newWeights;
    int outputLayerIndex = this->layers.size()-1;

    // 1. Calculating Output Layer Gradient
    Matrix derivedOutput = layers[outputLayerIndex]->matrixifyDerivedVals();
    Matrix gradients(1, derivedOutput.getNumCols(), false);
    
    for (int i = 0; i < this->errors.size(); i++) {
        double gradient = derivedOutput.getValue(0, i) * errors[i];
        gradients.setValue(0, i, gradient);
    }

    // 2. Processing output layer weights
    int lastHiddenIndex         = outputLayerIndex - 1;
    Matrix* outputWeights       = weightMatrices[lastHiddenIndex];
    Matrix activatedHidden      = layers[lastHiddenIndex]->matrixifyActivatedVals();

    // Calculating weight deltas
    Matrix deltaWeights         = (gradients.transpose() * activatedHidden).transpose();

    // Creating updated weights
    Matrix* newOutputWeights    = new Matrix(outputWeights->getNumRows(),
                                            outputWeights->getNumCols(),
                                            false);

    for (int r = 0; r < newOutputWeights->getNumRows(); r++) {
        for (int c = 0; c < newOutputWeights->getNumCols(); c++) {
            double originalWeight   = outputWeights->getValue(r, c);
            double deltaWeight      = deltaWeights.getValue(r, c);
            double newWeight        = originalWeight - deltaWeight;

            newOutputWeights->setValue(r, c, newWeight);
        }
    }

    newWeights.push_back(newOutputWeights);
    Matrix currentGradient = gradients;

    // 3. Processing the hidden layers
    for (int i = (lastHiddenIndex); i > 0; i--) {
        Layer *currentLayer         = this->layers.at(i);
        Matrix derivedHidden        = currentLayer->matrixifyDerivedVals();
        Matrix activatedHidden      = currentLayer->matrixifyActivatedVals();
        Matrix *weightMatrix        = this->weightMatrices.at(i);
        Matrix *originalWeight      = this->weightMatrices.at(i - 1);

        // Calculating the hidden layer gradients
        Matrix hiddenGradients(1, currentLayer->getNeurons().size(), false);

        for (int r = 0; r < weightMatrix->getNumRows(); r++) {
            double sum = 0.00;

            for (int c = 0; c < weightMatrix->getNumCols(); c++) {
                double p = currentGradient.getValue(0, c) * weightMatrix->getValue(r, c);
                sum += p;
            }

            double gradient = sum * derivedHidden.getValue(0, r);
            hiddenGradients.setValue(0, r, gradient);
        }

        // Getting previous layer values
        Matrix prevNeurons = (i - 1 == 0) ?
        this->layers.at(0)->matrixifyVals() :
        this->layers[i-1]->matrixifyActivatedVals();

        // Calculating delta weights
        Matrix hiddenDelta = (hiddenGradients.transpose() * prevNeurons).transpose();

        // Creating updated weights
        Matrix *newHiddenWeights = new Matrix(
                                    originalWeight->getNumRows(),
                                    originalWeight->getNumCols(),
                                    false
                                );
        
        for (int r = 0; r < newHiddenWeights->getNumRows(); r++) {
            for (int c = 0; c < newHiddenWeights->getNumCols(); c++) {
                double w = originalWeight->getValue(r, c);
                double d = hiddenDelta.getValue(r, c);
                double newWeight = w - (this->learningRate * d);    // new weight
                newHiddenWeights->setValue(r, c, newWeight);
            }
        }

        newWeights.push_back(newHiddenWeights);
        currentGradient = hiddenGradients;
    }

    // std::cout << "Done with back prop" << std::endl;
    // std::cout << "New weights size: " << newWeights.size() << std::endl;
    // std::cout << "Old weights size: " << this->weightMatrices.size() << std::endl;

    // 4. Update Weights
    std::reverse(newWeights.begin(), newWeights.end());

    // Cleaning up old weights
    for (Matrix* weight : weightMatrices) {
        delete weight;
    }

    weightMatrices = newWeights;
}