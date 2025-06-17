#include "../../headers/NeuralNetwork.h"

void NeuralNetwork::feedForward() {
    for (int i = 0; i < (layers.size() - 1); i++) {
        Matrix a = this->getNeuronMatrix(i);

        if (i != 0) {
            a = this->getActivatedNeuronMatrix(i);
        }

        Matrix* b = getWeightMatrix(i);
        Matrix c = a * (*b);    // *b = value of b (dereference)

        for (int c_index = 0; c_index < c.getNumCols(); c_index++) {
            this->setNeuronValue(i + 1, c_index, c.getValue(0, c_index));
        }
    }
}