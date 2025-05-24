#ifndef _NEURON_H_
#define _NEURON_H_4

#include <iostream>

class Neuron {
public:

    // Constructor
    Neuron(double val);

    // Setters

    /*
    I am gopnna use a sigmoid function to activate a neuron
    because it is easy to get it's derivative
    f(x) = x / (1 + |x|)
    */
    void activate();

    /*
    derivative of fast sigmoid function
    f'(x) = f(x) * (1 - f(x))
    */
    void derive();


    //  Getters
    double getVal() { return this->val; }
    double getActivatedVal() { return this->activatedVal; }
    double getDerivedVal() { return this->derivedVal; }

private:
    // The current value of the neuron
    double val;

    // The activation value of the neuron
    // This is also the squeezed value of the val
    double activatedVal;

    // The approximated deerivative of the direct value
    double derivedVal;


};


#endif