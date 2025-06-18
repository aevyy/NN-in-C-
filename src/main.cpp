#include <iostream>
#include <vector>
#include "../headers/Neuron.h"
#include "../headers/NeuralNetwork.h"
#include "../headers/utils/DataLoader.h"


using namespace std;

int main() {

    vector<vector<double>> rows = utils::DataLoader::fetchData("../src/test_data.csv");
    cout << "Rows loaded: " << rows.size() << endl;
    for (size_t i = 9; i < rows.size(); i++) {
        cout << "Row " << i << " size: " << rows[i].size() << endl;
    }

    cout << "Setting input" << endl;
    vector<double> input = rows[0];
    cout << "Successfully set input" << endl;

    cout << "Setting target" << endl;
    vector<double> target = rows[3];
    cout << "Successfully set target" << endl;


    // vector<double> input;
    // input.push_back(1);
    // input.push_back(0);
    // input.push_back(1);

    vector<int> topology;
    cout << "Topology push backk" << endl;
    topology.push_back(4);
    topology.push_back(2);
    topology.push_back(4);
    cout << "Complete topology push back" << endl;

    vector<ActivationType> activations = {
                                            SIGM,
                                            RELU,
                                            SIGM
                                        };

    double learningRate = 0.9;

    NeuralNetwork *nn = new NeuralNetwork(topology, activations, learningRate);
    cout << "About to call setCurrentInput" << endl;
    nn->setCurrentInput(input);
    cout << ">>> About to call setCurrentTarget()\n";
    nn->setCurrentTarget(target);
    cout << ">>> Returned from setCurrentTarget()\n";

    // Training  process
    // Lets run it 10 times to test if the error is decreasing
    for (int i = 0; i < 100; i++) {
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
    // cout << "HISTORICAL ERRORS: \n";
    // nn->printHistoricalErrors();


    delete nn;

    return 0;
}