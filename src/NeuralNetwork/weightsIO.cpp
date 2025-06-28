#include "../../headers/NeuralNetwork.h"
#include <sstream>
#include <iomanip>

void NeuralNetwork::saveWeights(const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Could not open file for saving weights: " << filename << std::endl;
        return;
    }
    
    out << std::fixed << std::setprecision(6);
    
    for (size_t layer = 0; layer < weightMatrices.size(); ++layer) {
        Matrix* mat = weightMatrices[layer];
        for (int row = 0; row < mat->getNumRows(); ++row) {
            for (int col = 0; col < mat->getNumCols(); ++col) {
                out << mat->getValue(row, col);
                if (col < mat->getNumCols() - 1) out << ",";
            }
            out << std::endl;
        }
        if (layer < weightMatrices.size() - 1) {
            out << "---" << std::endl; // layer separator
        }
    }
    
    out.close();
}

void NeuralNetwork::loadWeights(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Could not open weights file: " << filename << std::endl;
        return;
    }
    
    std::string line;
    size_t currentLayer = 0;
    int currentRow = 0;
    
    while (std::getline(in, line) && currentLayer < weightMatrices.size()) {
        if (line == "---") {
            currentLayer++;
            currentRow = 0;
            continue;
        }
        
        if (line.empty() || line[0] == '#') continue;
        
        std::stringstream ss(line);
        std::string cell;
        Matrix* mat = weightMatrices[currentLayer];
        
        for (int col = 0; col < mat->getNumCols() && std::getline(ss, cell, ','); col++) {
            mat->setValue(currentRow, col, std::stod(cell));
        }
        currentRow++;
    }
    
    in.close();
}