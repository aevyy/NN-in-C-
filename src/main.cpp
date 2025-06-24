#include <iostream>
#include <vector>
#include "../headers/Neuron.h"
#include "../headers/NeuralNetwork.h"
#include "../headers/utils/DataLoader.h"


using namespace std;

int main() {

    vector<double> input{0.2,0.5,0.1};
    vector<double> target{0.2,0.5,0.1};

    double learningRate = 0.5;
    double momentum = 1;
    double bias = 1;

    vector<int> topology{3, 2, 3};

    NeuralNetwork *n = new NeuralNetwork(topology);
    n->setCurrentInput(input);
    n->setCurrentTarget(target);


    for (int i = 0; i < 10000; i++) {
        cout << "EPOCH: " << i + 1 << endl;
        n -> train(
            input,
            target,
            bias,
            learningRate,
            momentum
        );


        cout << "OUTPUT: \n";
        n->printOutputToConsole();
        cout << "\nTarget: \n";
        n->printTargetToConsole();
    }
    n->printHistoricalErrors();


    return 0;
}