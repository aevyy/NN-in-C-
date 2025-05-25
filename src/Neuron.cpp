#include "../headers/Neuron.h"
#include <cmath>

void Neuron::setVal(double val) {
    this->val = val;
    activate();
    derive();
}

// Constructor
Neuron::Neuron(double val) {
    this->val = val;
    activate();
    derive();
}

/*
I am gopnna use a sigmoid function to activate a neuron
because it is easy to get it's derivative
f(x) = x / (1 + |x|)
*/
void Neuron::activate() {
    this->activatedVal = this->val / (1 + std::abs(this->val));
}

/*
derivative of fast sigmoid function
f'(x) = f(x) * (1 - f(x))
*/
void Neuron::derive() {
    this->derivedVal = this->activatedVal * (1 - this->activatedVal);
}