#include <iostream>
#include "../header/Neuron.h"

using namespace std;

int main() {
    Neuron *n = new Neuron(0.8);
    
    // Initial tests
    cout << "Value: " << n->getVal() << endl;
    cout << "Activated Value: " << n->getActivatedVal() << endl;
    cout << "Derived Value: " << n->getDerivedVal() << endl;

    return 0;
}