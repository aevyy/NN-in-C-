#include "../headers/Matrix.h"

// Default constructor: creates an empty matrix
Matrix::Matrix()
    : numRows(0),
      numCols(0),
      values()
{}

// Constructor: create matrix of given size,
// optionally filled with random values
Matrix::Matrix(int numRows, int numCols, bool isRandom) {
    this->numRows = numRows;
    this->numCols = numCols;

    // Fill matrix with either random or zero
    for (int i = 0; i < numRows; i++) {
        std::vector<double> colVals;
        
        for (int j = 0; j < numCols; j++) {
            double r = isRandom ? this->generateRandomNumber() : 0.00;
            colVals.push_back(r);
        }

        // Stack the colVals -> Matrix
        this->values.push_back(colVals);
    }
}

// Transpose: rows <-> columns interchange
Matrix Matrix::transpose() const {
    Matrix m(this->numCols, this->numRows, false);
    for (int i = 0; i < this->numRows; i++) {
        for (int j = 0; j < this->numCols; j++) {
            m.setValue(j, i, this->getValue(i, j));
        }
    }

    return m;
}

Matrix Matrix::duplicate() const {
    Matrix m(this->numRows, this->numCols, false);
    for (int i = 0; i < this->numRows; i++) {
        for (int j = 0; j < this->numCols; j++) {
            m.setValue(i, j, this->getValue(i, j));
        }
    }

    return m;
}

double Matrix::generateRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-.0001, .0001);

    return dis(gen);
}

void Matrix::printToConsole() const {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << this->values.at(i).at(j) << "\t\t";
        }
        
        std::cout << std::endl;
    }
}