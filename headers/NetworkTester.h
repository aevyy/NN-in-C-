#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "../NeuralNetwork.h"
#include "../utils/DataLoader.h"
#include "../json.hpp"

using json = nlohmann::json;

namespace NetworkTester {
    /**
     * Test a neural network using configuration from test.json
     */
    void testWithConfig();
    
    /**
     * Show test sample results
     */
    void showSample(const std::vector<double>& input, class NeuralNetwork& network, int num);
}
