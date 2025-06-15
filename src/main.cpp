#include <iostream>
#include <vector>
#include "../headers/Neuron.h"
#include "../headers/NeuralNetwork.h"


using namespace std;

int main() {
    vector<double> input;
    input.push_back(1);
    input.push_back(0);
    input.push_back(1);

    vector<int> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(3);

    NeuralNetwork *nn = new NeuralNetwork(topology);
    nn->setCurrentInput(input);
    cout << ">>> About to call setCurrentTarget()\n";
    nn->setCurrentTarget(input);
    cout << ">>> Returned from setCurrentTarget()\n";

    // Training  process
    // Lets run it 10 times to test if the error is decreasing
    for (int i = 0; i < 1000; i++) {
        // cout << ">>>About to call feedForward()\n";
        nn->feedForward();
        // cout << ">>>Returned from feedForward()\n";

        // cout << ">>> About to call setErrors() \n";
        nn->setErrors();
        // cout << ">>>Returned from setErrors()\n";

        // cout << ">>> About to call printToConsole()\n";
        // nn->printToConsole();
        // cout << ">>> Returned from printToConsole()\n";
        cout << "Epoch: " << i + 1 << endl;
        cout << "Total errors: " << nn->getTotalError() << endl;

        // cout << ">>> About to call backPropagation()\n";
        nn->backPropagation();
        // cout << ">>> Returned from backPropagation()\n";

        // To compare input, target, and output
        cout << "=====================" << endl;
        cout << "OUTPUT: ";
        nn->printOutputToConsole();

        cout << "=====================" << endl;
        cout << "TARGET: "; 
        nn->printTargetToConsole();
        
        cout << endl;
        
    }

    return 0;
}