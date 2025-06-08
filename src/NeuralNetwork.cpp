#include "../headers/NeuralNetwork.h"

void NeuralNetwork::backPropagation() {
    std::vector <Matrix *> newWeights;
    // Output to hidden
    int outputLayerIndex        = this->layers.size()-1;
    Matrix *derivedValuesYToZ   = this->layers.at(outputLayerIndex)->matrixifyDerivedVals();
    // Creating a matrix of     dimentions 1 * size of output layer
    Matrix *gradientsYToZ       = new Matrix(1, this->layers.at(outputLayerIndex)->getNeurons().size(), false);
    
    for (int i = 0; i < this->errors.size(); i++) {
        double d = derivedValuesYToZ->getValue(1, i);
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
    
//     // Moving from the last hidden layer down to the input layer
//     for (int i = (lastHiddenLayerIndex); i >= 0; i--) {
        
//     }

// 
}

void NeuralNetwork::setErrors() {
    if (this->target.size() == 0) {
        std::cerr << "No target for this Neural Network." << std::endl;
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
        // I have used the simplest cost function to determine the error
        double tempErr = (outputNeurons.at(i) ->getActivatedVal() - target.at(i));
        errors.at(i) = tempErr;
        this->error += tempErr;
    }
    // Keepint track of all the errors on each iteration
    historicalErrors.push_back(this->error);
}

void NeuralNetwork::feedForward() {
    for (int i = 0; i < (this->layers.size() - 1); i++) {
        Matrix *a = this->getNeuronMatrix(i);

        if (i != 0) {
            a = this->getActivatedNeuronMatrix(i);
        }

        Matrix *b = this->getWeightMatrix(i);
        Matrix *c = (new utils::MultiplyMatrix(a, b))->execute();

        for (int c_index = 0; c_index < c->getNumCols(); c_index++) {
            this->setNeuronValue(i + 1, c_index, c->getValue(0, c_index));
        }
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

void NeuralNetwork::setCurrentInput(std::vector<double> input) {
    this->input = input;

    for (int i = 0; i < input.size(); i++) {
        this->layers.at(0)->setVal(i, input.at(i));
    }
}

void NeuralNetwork::setCurrentTarget(std::vector<double> target) {
    this->target = target;
}



// Constructor for NeuralNetwork class
NeuralNetwork::NeuralNetwork(std::vector<int> topology) {
    // Saving the topology and computing it's size
    this->topology = topology;
    this->topologySize = topology.size();

    // Creating the layers based on the topology
    for (int i = 0; i < topologySize; i++) {
        Layer *l = new Layer(topology.at(i));
        this->layers.push_back(l);
    }

    // Creating the weight matrix connecting
    // each layer to the next
    for (int i = 0; i < (topologySize - 1); i++) {
        // Matrix dimentions: current layer size * next layer size
        Matrix *m = new Matrix(topology.at(i), topology.at(i+1), true);
        this->weightMatrices.push_back(m);
    }
}