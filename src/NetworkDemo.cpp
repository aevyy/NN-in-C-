#include "../../headers/NetworkDemo.h"

namespace NetworkDemo {
    
    void runDemoTests() {
        std::cout << ">> Running Neural Network Demos\n" << std::endl;
        
        testBasicNetwork();
        testDataLoader();
        testConfigLoader();
        
        std::cout << "\n>> All demos completed!" << std::endl;
    }
    
    void testBasicNetwork() {
        std::cout << "1. Basic Network Test" << std::endl;
        
        // Simple autoencoder test
        std::vector<int> topology = {4, 6, 4};
        NeuralNetwork nn(topology, 1.0, 0.1, 0.9);
        
        std::vector<double> input = {0.1, 0.5, 0.8, 0.3};
        
        // Test before training
        nn.setCurrentInput(input);
        nn.feedForward();
        std::cout << "Input: 0.1 0.5 0.8 0.3" << std::endl;
        std::cout << "Before: ";
        nn.printOutputToConsole();
        
        // Quick training
        for (int i = 0; i < 100; i++) {
            nn.train(input, input, 1.0, 0.1, 0.9);
        }
        
        // Test after training
        nn.setCurrentInput(input);
        nn.feedForward();
        std::cout << "After: ";
        nn.printOutputToConsole();
        std::cout << "Error: " << std::setprecision(6) << nn.getTotalError() << std::endl;
    }
    
    void testDataLoader() {
        std::cout << "\n2. Data Loading Test" << std::endl;
        
        try {
            auto data = utils::Misc::fetchData("data/train.csv");
            if (!data.empty()) {
                std::cout << "Loaded " << data.size() << " samples" << std::endl;
                std::cout << "Sample: ";
                for (int i = 0; i < std::min(4, (int)data[0].size()); i++) {
                    std::cout << data[0][i] << " ";
                }
                std::cout << std::endl;
            } else {
                std::cout << "No data found" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Data loading failed: " << e.what() << std::endl;
        }
    }
    
    void testConfigLoader() {
        std::cout << "\n3. Config Loading Test" << std::endl;
        
        try {
            std::ifstream file("config/train.json");
            if (!file.is_open()) {
                std::cout << "No config file found" << std::endl;
                return;
            }
            
            json config;
            file >> config;
            file.close();
            
            std::cout << "Topology: ";
            for (int v : config["topology"]) std::cout << v << " ";
            std::cout << std::endl;
            std::cout << "Learning Rate: " << config["learningRate"] << std::endl;
            std::cout << "Epochs: " << config["epochs"] << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "Config loading failed: " << e.what() << std::endl;
        }
    }
}
