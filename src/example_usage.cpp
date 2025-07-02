// Example usage of the Neural Network implementation
// This file demonstrates practical usage patterns

#include <iostream>
#include <fstream>
#include "../headers/NeuralNetwork.h"
#include "../headers/utils/DataLoader.h"
#include "../headers/json.hpp"

using json = nlohmann::json;

void trainXORExample() {
    std::cout << "\n=== XOR Training Example ===" << std::endl;
    
    // Create a simple network for XOR problem
    std::vector<int> topology = {2, 4, 1}; // 2 inputs, 4 hidden neurons, 1 output
    NeuralNetwork nn(topology, TANH, SIGM, COST_MSE, 1.0, 0.5, 0.9);
    
    // XOR training data
    std::vector<std::vector<double>> inputs = {
        {0, 0}, {0, 1}, {1, 0}, {1, 1}
    };
    std::vector<std::vector<double>> targets = {
        {0}, {1}, {1}, {0}
    };
    
    std::cout << "Training XOR function..." << std::endl;
    
    // Train for multiple epochs
    for (int epoch = 0; epoch < 1000; epoch++) {
        double totalError = 0.0;
        
        for (int i = 0; i < inputs.size(); i++) {
            nn.train(inputs[i], targets[i], 1.0, 0.5, 0.9);
            totalError += nn.getTotalError();
        }
        
        if (epoch % 100 == 0) {
            std::cout << "Epoch " << epoch << ", Average Error: " << totalError / inputs.size() << std::endl;
        }
    }
    
    // Test the trained network
    std::cout << "\nTesting XOR function:" << std::endl;
    for (int i = 0; i < inputs.size(); i++) {
        nn.setCurrentInput(inputs[i]);
        nn.feedForward();
        
        std::cout << "Input: " << inputs[i][0] << ", " << inputs[i][1] 
                  << " | Expected: " << targets[i][0] 
                  << " | Got: ";
        nn.printOutputToConsole();
    }
}

void autoencoderExample() {
    std::cout << "\n=== Autoencoder Example ===" << std::endl;
    
    // Load configuration for autoencoder
    try {
        std::ifstream configFile("config/train.json");
        if (configFile.is_open()) {
            json config;
            configFile >> config;
            
            std::vector<int> topology = config["topology"];
            double learningRate = config["learningRate"];
            double momentum = config["momentum"];
            double bias = config["bias"];
            
            std::cout << "Creating autoencoder with topology: ";
            for (int i = 0; i < topology.size(); i++) {
                std::cout << topology[i];
                if (i < topology.size() - 1) std::cout << "-";
            }
            std::cout << std::endl;
            
            NeuralNetwork autoencoder(topology, RELU, SIGM, COST_MSE, bias, learningRate, momentum);
            
            // Generate some sample data for autoencoder training
            std::vector<double> sampleInput(topology[0], 0.0);
            for (int i = 0; i < topology[0]; i++) {
                sampleInput[i] = static_cast<double>(rand()) / RAND_MAX;
            }
            
            // For autoencoder, target = input
            std::vector<double> target = sampleInput;
            
            std::cout << "Training autoencoder for reconstruction..." << std::endl;
            
            for (int epoch = 0; epoch < 10; epoch++) {
                autoencoder.train(sampleInput, target, bias, learningRate, momentum);
                if (epoch % 2 == 0) {
                    std::cout << "Epoch " << epoch << ", Reconstruction Error: " 
                              << autoencoder.getTotalError() << std::endl;
                }
            }
            
            configFile.close();
        } else {
            std::cout << "Could not open config file, using default parameters" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error in autoencoder example: " << e.what() << std::endl;
    }
}

void classificationExample() {
    std::cout << "\n=== Binary Classification Example ===" << std::endl;
    
    // Simple binary classification network
    std::vector<int> topology = {4, 6, 3, 1}; // 4 features -> 1 binary output
    NeuralNetwork classifier(topology, RELU, SIGM, COST_MSE, 1.0, 0.1, 0.8);
    
    // Generate some sample classification data
    std::vector<std::vector<double>> features = {
        {0.1, 0.2, 0.3, 0.4}, // Class 0
        {0.9, 0.8, 0.7, 0.6}, // Class 1
        {0.2, 0.1, 0.4, 0.3}, // Class 0
        {0.8, 0.9, 0.6, 0.7}, // Class 1
        {0.3, 0.4, 0.1, 0.2}, // Class 0
        {0.7, 0.6, 0.9, 0.8}  // Class 1
    };
    
    std::vector<std::vector<double>> labels = {
        {0.0}, {1.0}, {0.0}, {1.0}, {0.0}, {1.0}
    };
    
    std::cout << "Training binary classifier..." << std::endl;
    
    for (int epoch = 0; epoch < 100; epoch++) {
        double totalError = 0.0;
        
        for (int i = 0; i < features.size(); i++) {
            classifier.train(features[i], labels[i], 1.0, 0.1, 0.8);
            totalError += classifier.getTotalError();
        }
        
        if (epoch % 20 == 0) {
            std::cout << "Epoch " << epoch << ", Classification Error: " 
                      << totalError / features.size() << std::endl;
        }
    }
    
    // Test classification
    std::cout << "\nTesting classifier:" << std::endl;
    for (int i = 0; i < features.size(); i++) {
        classifier.setCurrentInput(features[i]);
        classifier.feedForward();
        
        std::cout << "Features: ";
        for (double f : features[i]) std::cout << f << " ";
        std::cout << "| Expected: " << labels[i][0] << " | Predicted: ";
        classifier.printOutputToConsole();
    }
}

int main() {
    std::cout << "=== Neural Network Examples ===" << std::endl;
    
    try {
        trainXORExample();
        autoencoderExample();
        classificationExample();
        
        std::cout << "\n=== All Examples Completed ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error in examples: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
