#include <iostream>
#include <vector>
#include "../headers/Neuron.h"
#include "../headers/NeuralNetwork.h"
#include "../headers/utils/DataLoader.h"


using namespace std;

int main() {

    const int inputSize = 4;
    const int targetSize = 4;
    const string path = "../src/test_data.csv";

    // Loading samples from file
    vector<utils::Sample> dataset = utils::DataLoader::fetchData(
        path,
        inputSize,
        targetSize
    );

    if (dataset.empty()) {
        cerr << "No valid data loaded from file: "
        << path << endl;
    }

    // Defiining topology and activation functions
    vector<int> topology = {4, 2, 4};
    vector<ActivationType> activations = {SIGM,RELU,SIGM};
    double learningRate = 0.9;

    NeuralNetwork* nn = new NeuralNetwork(topology, RELU, SIGM, COST_MSE, 1, learningRate, 1);

    int epochs = 1000;

    for (int i = 0; i < epochs; i++) {
        cout << "EPOCH: " << i + 1 << endl;

        for (const auto& [input, target] : dataset) {
            nn->setCurrentInput(input);
            nn->setCurrentTarget(target);

            nn->feedForward();
            nn->setErrors();
            nn->backPropagation();
        }

        cout << "Total error: " << nn->getTotalError() << endl;

        cout << "==============================" << endl;
        cout << "OUTPUT: ";
        nn->printOutputToConsole();
        cout << endl << "==============================" << endl;
        cout << "TARGET: ";
        nn->printTargetToConsole();
        cout << endl;
    }

    // Test: Save weights to file after training
    nn->saveWeights("weights_test.csv");
    std::cout << "Weights saved to weights_test.csv" << std::endl;

    delete nn;
    return 0;
}