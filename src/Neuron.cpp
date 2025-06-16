#include "../headers/Neuron.h"
#include <cmath>

// Constructors
Neuron::Neuron(double val) {
    this->activationType = SIGM;
    this->setVal(val);
}

Neuron::Neuron(double val, ActivationType activationType) {
    this->activationType = activationType;
    this->setVal(val);
}

void Neuron::setVal(double val) {
    this->val = val;
    activate();
    derive();
}

void Neuron::activate() {
    if(activationType == TANH) {
        this->activatedVal = tanh(this->val);
        return;
    }
    
    if (activationType == RELU) {
        activatedVal = (val > 0) ? val : 0;
        return;
    }

    // SIGM or fallback
    activatedVal = 1 / (1 + exp(-this->val));
}

void Neuron::derive() {
    if(activationType == TANH) {
        this->derivedVal = (1 - (this->activatedVal * this->activatedVal));
        return;
    }
    
    if (activationType == RELU) {
        derivedVal = (val > 0) ? 1.0 : 0.0;
        return;
    }

    // SIGM or fallback
    derivedVal = (this->activatedVal * (1 - this->activatedVal));
}