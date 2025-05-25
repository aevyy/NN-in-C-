#include <iostream>
#include "../headers/Neuron.h"
#include "../headers/Layer.h"
#include "../headers/Matrix.h"

using namespace std;

int main() {

    Matrix *m = new Matrix(3, 2, true);
    m->printToConsole();

    return 0;
}