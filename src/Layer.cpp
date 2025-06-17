#include "../headers/Layer.h"

Layer::Layer(int size) : size(size) {
    for (int i = 0; i < size; i++) {
        Neuron *n = new Neuron(0.00);
        this->neurons.push_back(n);
    }
}

Layer::Layer(int size, ActivationType activationType) : size(size) {
    for (int i = 0; i < size; i++) {
        Neuron *n = new Neuron(0.00, activationType);
        neurons.push_back(n);
    }
}

Layer::~Layer() {
    for (Neuron* neuron : neurons) {
        delete neuron;  // To clean up dynamically allocated neurons
    }
}

void Layer::setNeuron(std::vector<Neuron*>& newNeurons) {
    // First, lets delete existing neurons to avoid memory leaks
    for (Neuron* neuron : neurons) {
        delete neuron;
    }
    neurons = newNeurons;   // Shallow copy
    newNeurons.clear();     //Transfer ownership
}

void Layer::setVal(int i, double v) {
    this->neurons.at(i)->setVal(v);
}

std::vector<double> Layer::getActivatedVals() const {
    std::vector<double> actVals;
    actVals.reserve(neurons.size());    // Pre-allocation for efficiency
    for (Neuron* neuron : neurons) {
        double val = neuron->getActivatedVal();
        actVals.push_back(val);
    }
    return actVals;
}

Matrix Layer::matrixifyVals() const {
    Matrix m(1, neurons.size(), false);
    for (int i = 0; i < this->neurons.size(); i++) {
        m.setValue(
            0,
            i,
            this->neurons.at(i)->getVal()
        );
    }
    return m;
}

Matrix Layer::matrixifyActivatedVals() const {
    Matrix m(1, this->neurons.size(), false);
    for (int i = 0; i < this->neurons.size(); i++) {
        m.setValue(
            0,
            i,
            this->neurons.at(i)->getActivatedVal()
        );
    }
    return m;
}

Matrix Layer::matrixifyDerivedVals() const {
    Matrix m(1, this->neurons.size(), false);
    for (int i = 0; i < this->neurons.size(); i++) {
        m.setValue(
            0,
            i,
            this->neurons.at(i)->getDerivedVal()
        );
    }
    return m;
}