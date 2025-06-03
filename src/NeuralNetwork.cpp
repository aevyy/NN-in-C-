#include "../headers/NeuralNetwork.h"

void NeuralNetwork::setErrors() {
    if (this->target.size() == 0) {
        std::cerr << "No target for this Neural Network." << std::endl;
        assert(false);
    }

    if (this->target.size() != this->layers.at(this->layers.size() - 1)->getNumNeurons()) {
        std::cerr << "Target size is not same at the output layer size: "
        << this->layers.at(this->layers.size() - 1)->getNumNeurons() << std::endl;
        assert(false);
    }

    this->error = 0.00;
    int outputLayerIndex = this->layers.size() - 1;
    std::vector<Neuron *> outputNeurons = this->layers.at(outputLayerIndex)->getNumNeurons();
    for (int i = 0; i < target.size(); i++) {
        double tempErr = (outputNeurons.at(i) ->getActivatedVal() -target.at(i));
        errors.at(i) = tempErr;
        this->error += tempErr;
    }
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
        this->weightMetrices.push_back(m);
    }
}