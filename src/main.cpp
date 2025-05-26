#include <iostream>
#include "../headers/Neuron.h"
#include "../headers/Layer.h"
#include "../headers/Matrix.h"

using namespace std;

int main() {

    // Tests and debugging
    Matrix *m = new Matrix(3, 2, true);
    m->printToConsole();

    cout << "_______________________" << endl << endl;
    // Transpose test
    Matrix *mT = m->transpose();

    mT->printToConsole();

    return 0;
}