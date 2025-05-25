#ifndef _LAYER_H_
#define _LAYER_H_

#include <iostream>
#include <vector>
#include "Neuron.h"

class Layer {
public:
    // Constructor
    Layer(int size);

private:
    int size;   // This is the size of neurons vector
    std::vector<Neuron *> neurons;  // This will contain the instances of Neuron
};


#endif