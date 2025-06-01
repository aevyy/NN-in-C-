#include "../headers/utils/MultiplyMatrix.h"

utils::MultiplyMatrix::MultiplyMatrix(Matrix *a, Matrix *b) {
    this->a = a;
    this->b = b;

    // If the matrix dimentions do not match for multiplication
    if (a->getNumCols() != b->getNumRows()) {
        std::cerr << "A_cols: " << a->getNumCols() 
        << "!= B_Rows: " << b->getNumRows()
        << std::endl;
        assert(false);
    }
    // If the matrices with m * n and n * p are multiplied,
    // the new matrix should have m * p dimensions.
    this->c = new Matrix(a->getNumRows(), b->getNumCols(), false);
}

Matrix *utils::MultiplyMatrix::execute() {
    for (int i = 0; i < a->getNumRows(); i++) {
        for (int j = 0; j < b->getNumCols(); j++) {
            for (int k = 0; k < b->getNumRows(); k++) {
                double p = this->a->getValue(i, k) * this->b->getValue(k, j);
                double newVal = this->c->getValue(i, j) + p;
                this->c->setValue(i, j, newVal);
            }
        }
    }
    return this->c;
}