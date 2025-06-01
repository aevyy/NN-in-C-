#include <iostream>
#include <vector>
#include "../headers/Neuron.h"
#include "../headers/NeuralNetwork.h"


using namespace std;

int main() {
    vector<double> input;
    input.push_back(1.0);
    input.push_back(0.0);
    input.push_back(1.0);

    vector<int> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);

    NeuralNetwork *nn = new NeuralNetwork(topology);
    nn->setCurrentInput(input);
std::cout << ">>> About to call feedForward()\n";
nn->feedForward();
std::cout << ">>> Returned from feedForward()\n";

std::cout << ">>> About to call printToConsole()\n";
nn->printToConsole();
std::cout << ">>> Returned from printToConsole()\n";



    return 0;
}