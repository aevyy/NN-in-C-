#include "../../headers/NeuralNetwork.h"

void NeuralNetwork::saveWeights(const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Could not open file for saving weights: " << filename << std::endl;
        return;
    }
    out << "# Neural Network Weights" << std::endl;
    for (size_t i = 0; i < weightMatrices.size(); ++i) {
        out << "# Weights between Layer " << i << " and Layer " << (i+1) << std::endl;
        Matrix* mat = weightMatrices[i];
        for (int r = 0; r < mat->getNumRows(); ++r) {
            for (int c = 0; c < mat->getNumCols(); ++c) {
                out << mat->getValue(r, c);
                if (c < mat->getNumCols() - 1) out << ",";
            }
            out << std::endl;
        }
    }
    out.close();
}