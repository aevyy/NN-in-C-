#include "../../headers/NeuralNetwork.h"

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