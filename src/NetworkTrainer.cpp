#include "../../headers/NetworkTrainer.h"
#include <iomanip>

namespace NetworkTrainer {
    
    void trainWithConfig() {
        std::ifstream file("config/train.json");
        if (!file.is_open()) throw std::runtime_error("Cannot open config/train.json");
        
        json config;
        file >> config;
        file.close();
        
        auto topology       = config["topology"].get<std::vector<int>>();
        double lr           = config["learningRate"];
        double momentum     = config["momentum"];
        double bias         = config["bias"];
        int epochs          = config["epochs"];
        auto data           = utils::Misc::fetchData(config["trainingData"]);
        
        if (data.empty()) throw std::runtime_error("No training data found");
        if (data[0].size() != topology[0]) {
            topology[0] = topology.back() = data[0].size();
        }
        
        NeuralNetwork nn(topology, RELU, SIGM, COST_MSE, bias, lr, momentum);
        
        for (int epoch = 0; epoch < epochs; epoch++) {
            double totalError = 0.0;
            for (auto& sample : data) {
                nn.train(sample, sample, bias, lr, momentum);
                totalError += nn.getTotalError();
            }
            
            // Show progress every 1000 epochs
            if (epoch % 1000 == 0 || epoch == epochs-1) {
                std::cout << "\nEpoch " << epoch+1 << "/" << epochs 
                         << " - Error: " << std::setprecision(4) << totalError/data.size() << std::endl;
                
                // Show first sample comparison
                nn.setCurrentInput(data[0]);
                nn.feedForward();
                
                std::cout << "  Input:  ";
                for (int j = 0; j < std::min(5, (int)data[0].size()); j++) {
                    std::cout << std::setprecision(2) << data[0][j] << " ";
                }
                std::cout << std::endl;
                
                std::cout << "  Target: ";
                for (int j = 0; j < std::min(5, (int)data[0].size()); j++) {
                    std::cout << std::setprecision(2) << data[0][j] << " ";
                }
                std::cout << std::endl;
                
                std::cout << "  Output: ";
                nn.printOutputToConsole();
                std::cout << std::endl;
            }
        }
        
        nn.saveWeights(config["weightsFile"]);
        showResults(data, nn);
    }
    
    void showResults(const std::vector<std::vector<double>>& data, NeuralNetwork& network) {
        for (int i = 0; i < std::min(3, (int)data.size()); i++) {
            network.setCurrentInput(data[i]);
            network.feedForward();

            std::cout << "Sample " << i+1 << ": " << std::endl;
            for (int j = 0; j < std::min(4, (int)data[i].size()); j++) {
                std::cout << std::setprecision(2) << data[i][j] << " ";
            }

            std::cout << "-> ";
            network.printOutputToConsole();
            std::cout << std::endl;
        }
    }
}
