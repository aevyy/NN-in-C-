#include "../../headers/NetworkTester.h"

namespace NetworkTester {
    
    void testWithConfig() {
        std::cout << ">> Testing Neural Network...\n" << std::endl;
        
        // Load config
        std::ifstream file("config/test.json");
        if (!file.is_open()) {
            std::cout << "ERROR: Can't find config/test.json" << std::endl;
            return;
        }
        
        json config;
        file >> config;
        file.close();
        
        // Setup from config
        auto topology = config["topology"].get<std::vector<int>>();
        std::string dataFile = config["testFile"];
        std::string weightsFile = config["weightsFile"];
        double bias = config["bias"];
        
        std::cout << "Network: " << topology[0] << " -> " << topology.back() << " nodes" << std::endl;
        std::cout << "Data: " << dataFile << std::endl;
        std::cout << "Weights: " << weightsFile << std::endl;
        
        // Load test data
        auto data = utils::Misc::fetchData(dataFile);
        if (data.empty()) {
            std::cout << "ERROR: No test data found!" << std::endl;
            return;
        }
        
        std::cout << "Loaded " << data.size() << " test samples (" << data[0].size() << " features each)" << std::endl;
        
        // Adjust topology for data size
        if (data[0].size() != topology[0]) {
            topology[0] = topology.back() = data[0].size();
        }
        
        // Create network
        NeuralNetwork nn(topology, RELU, SIGM, COST_MSE, bias, 0.05, 1.0);
        
        // Try to load weights
        std::ifstream weightsCheck(weightsFile);
        if (weightsCheck.is_open()) {
            weightsCheck.close();
            nn.loadWeights(weightsFile);
            std::cout << ">> Loaded trained weights" << std::endl;
        } else {
            std::cout << "WARNING: No weights found - using random weights" << std::endl;
        }
        
        std::cout << "\nRunning tests..." << std::endl;
        
        // Test all samples
        double totalError = 0.0;
        for (size_t i = 0; i < data.size(); i++) {
            nn.setCurrentInput(data[i]);
            nn.setCurrentTarget(data[i]); // autoencoder
            nn.feedForward();
            nn.setErrors();
            totalError += nn.getTotalError();
            
            // Show first few samples
            if (i < 3) showSample(data[i], nn, i + 1);
        }
        
        // Final results
        double avgError = totalError / data.size();
        std::cout << "\n>> Results: " << data.size() << " samples tested" << std::endl;
        std::cout << "Average error: " << std::fixed << std::setprecision(4) << avgError << std::endl;
        
        if (avgError < 0.1) std::cout << ">> Excellent! Network performs very well" << std::endl;
        else if (avgError < 0.5) std::cout << ">> Good performance" << std::endl;
        else std::cout << ">> Poor performance - network needs more training" << std::endl;
    }
    
    void showSample(const std::vector<double>& input, NeuralNetwork& network, int num) {
        std::cout << "Sample " << num << ": [";
        for (int j = 0; j < std::min(4, (int)input.size()); j++) {
            std::cout << std::setprecision(2) << input[j];
            if (j < std::min(4, (int)input.size()) - 1) std::cout << ", ";
        }
        if (input.size() > 4) std::cout << "...";
        std::cout << "] -> ";
        
        network.printOutputToConsole();
        std::cout << " (error: " << std::setprecision(4) << network.getTotalError() << ")" << std::endl;
    }
}
