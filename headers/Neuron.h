#pragma once

enum ActivationType { TANH = 1, RELU = 2, SIGM = 3 };

#include <iostream>
#include <cmath>

class Neuron {
public:
    Neuron(double val);
    Neuron(double val, ActivationType activationType);

    void activate();

    void derive();

    // Mutator
    void setVal(double v);

    //  Accessors
    double getVal() { return this->val; }
    double getActivatedVal() { return this->activatedVal; }
    double getDerivedVal() { return this->derivedVal; }

private:
    double val, activatedVal, derivedVal;
    ActivationType activationType;
};