#include "../../headers/NeuralNetwork.h"

void NeuralNetwork::backPropagation() {
    std::vector <Matrix *> newWeights;
    Matrix *gradient;
    // Output to hidden
    int outputLayerIndex        = this->layers.size()-1;
    Matrix *derivedValuesYToZ   = this->layers.at(outputLayerIndex)->matrixifyDerivedVals();
    // Creating a matrix of     dimentions 1 * size of output layer
    Matrix *gradientsYToZ       = new Matrix(1, this->layers.at(outputLayerIndex)->getNeurons().size(), false);
    
    for (int i = 0; i < this->errors.size(); i++) {
        double d = derivedValuesYToZ->getValue(0, i);
        double e = this->errors.at(i);
        double g = d * e;
        gradientsYToZ->setValue(0, i, g);
    }

    int lastHiddenLayerIndex        = outputLayerIndex - 1;
    Layer *lastHiddenLayer          = this->layers.at(lastHiddenLayerIndex);
    Matrix *weightOutputToHidden    = this->weightMatrices.at(lastHiddenLayerIndex);
    Matrix *deltaOutputToHidden     = (new utils::MultiplyMatrix(
                                        gradientsYToZ->transpose(),
                                        lastHiddenLayer->matrixifyActivatedVals()
                                    ))->execute()->transpose();

    Matrix *newWeightsOutputToHidden = new Matrix(
                                        deltaOutputToHidden->getNumRows(),
                                        deltaOutputToHidden->getNumCols(),
                                        false
                                    );

    for (int r = 0; r < deltaOutputToHidden->getNumRows(); r++) {
        for (int c = 0; c < deltaOutputToHidden->getNumCols(); c++) {
            double originalWeight = weightOutputToHidden->getValue(r, c);
            double deltaWeight = deltaOutputToHidden->getValue(r, c);
            newWeightsOutputToHidden->setValue(r, c, (originalWeight - deltaWeight));
        }
    }

    newWeights.push_back(newWeightsOutputToHidden);

    gradient = new Matrix(gradientsYToZ->getNumRows(), gradientsYToZ->getNumCols(), false);
    for (int r = 0; r < gradientsYToZ->getNumRows(); r++) {
        for (int c = 0; c < gradientsYToZ->getNumCols(); c++) {
            gradient->setValue(r, c, gradientsYToZ->getValue(r, c));
        }
    }
    
    // Moving from the last hidden layer down to the first
    for (int i = (lastHiddenLayerIndex); i > 0; i--) {
        Layer *l                    = this->layers.at(i);
        Matrix *derivedHidden       = l->matrixifyDerivedVals();
        Matrix *activatedHidden     = l->matrixifyActivatedVals();
        Matrix *derivedGradients    = new Matrix(
                                        1,
                                        l->getNeurons().size(),
                                        false
                                    );
        Matrix *weightMatrix        = this->weightMatrices.at(i);
        Matrix *originalWeight      = this->weightMatrices.at(i - 1);

        for (int r = 0; r < weightMatrix->getNumRows(); r++) {
            double sum = 0;
            for (int c = 0; c < weightMatrix->getNumCols(); c++) {
                double p = gradient->getValue(0, c) * weightMatrix->getValue(r, c);
                sum += p;
            }

            double g = sum * activatedHidden->getValue(0, r);
            derivedGradients->setValue(0, r, g);
        }

        Matrix *leftNeurons = (i - 1 == 0) ?
        this->layers.at(0)->matrixifyVals() : this->layers.at(i - 1) ->matrixifyActivatedVals();

        Matrix *deltaWeights = (new utils::MultiplyMatrix(derivedGradients->transpose(), leftNeurons))->execute() ->transpose();
        
        Matrix *newWeightsHidden = new Matrix(
                                    deltaWeights->getNumRows(),
                                    deltaWeights->getNumCols(),
                                    false
                                );
        
        for (int r = 0; r < newWeightsHidden->getNumRows(); r++) {
            for (int c = 0; c < newWeightsHidden->getNumCols(); c++) {
                double w = originalWeight->getValue(r, c);
                double d = deltaWeights->getValue(r, c);
                double n = w - d;    // new weight
                newWeightsHidden->setValue(r, c, n);
            }
        }

        gradient = new Matrix(derivedGradients->getNumRows(), derivedGradients->getNumCols(), false);
        for (int r = 0; r < derivedGradients->getNumRows(); r++) {
            for (int c = 0; c < derivedGradients->getNumCols(); c++) {
                gradient->setValue(r, c, derivedGradients->getValue(r, c));
            }
        }

        newWeights.push_back(newWeightsHidden);
    }
    // std::cout << "Done with back prop" << std::endl;
    // std::cout << "New weights size: " << newWeights.size() << std::endl;
    // std::cout << "Old weights size: " << this->weightMatrices.size() << std::endl;

    // Reversing the new weights (function from <algorithm>)
    std::reverse(newWeights.begin(), newWeights.end());
    this->weightMatrices = newWeights;
}