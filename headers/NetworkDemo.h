#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "../NeuralNetwork.h"
#include "../utils/DataLoader.h"
#include "../json.hpp"

using json = nlohmann::json;

namespace NetworkDemo {
    /**
     * Run demo tests
     */
    void runDemoTests();
    
    /**
     * Test basic network functionality
     */
    void testBasicNetwork();
    
    /**
     * Test data loading
     */
    void testDataLoader();
    
    /**
     * Test configuration loading
     */
    void testConfigLoader();
}
