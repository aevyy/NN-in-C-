#include <iostream>
#include <string>
#include "../headers/NetworkTrainer.h"
#include "../headers/NetworkTester.h"
#include "../headers/NetworkDemo.h"

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            std::cout << ">> Neural Network System" << std::endl;
            std::cout << "Usage: main [train|test|demo]" << std::endl;
            return 0;
        }
        
        std::string mode = argv[1];
        
        if (mode == "train") {
            NetworkTrainer::trainWithConfig();
        } else if (mode == "test") {
            NetworkTester::testWithConfig();
        } else if (mode == "demo") {
            NetworkDemo::runDemoTests();
        } else {
            std::cout << "ERROR: Unknown mode: " << mode << std::endl;
            std::cout << "Available modes: train, test, demo" << std::endl;
            return 1;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
