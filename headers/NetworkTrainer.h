#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "../NeuralNetwork.h"
#include "../utils/DataLoader.h"
#include "../json.hpp"

using json = nlohmann::json;

namespace NetworkTrainer {
    /**
     * Train a neural network using configuration from train.json
     * Handles data loading, network creation, training loop, and weight saving
     */
    void trainWithConfig();
    
    /**
     * Show sample results from training data
     */
    void showResults(const std::vector<std::vector<double>>& data, class NeuralNetwork& network);
}
