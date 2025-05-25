#include "../headers/Matrix.h"
#include <random>
#include <vector>

double Matrix::generateRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    return dis(gen);
}

// Function to print the elements in the matrix
// Mainly, this function is gonna help me debug
void Matrix::printToConsole() {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << this->values.at(i).at(j) << "\t\t";
        }
        std::cout << std::endl;
    }
}

Matrix::Matrix(int numRows, int numCols, bool isRandom) {
    this->numRows = numRows;
    this->numCols = numCols;

    for (int i = 0; i < numRows; i++) {
        // Lets make a vector where we'll
        // have our column values
        std::vector<double> colValues;

        for (int j = 0; j < numCols; j++) {
            double r = 0.00;
            if (isRandom) {
                r = this->generateRandomNumber();
            }
            // Lets add the random elements to our vector
            colValues.push_back(r);
        }

        // This is basically stacking the columns
        // on top of each other to make a matrix
        this->values.push_back(colValues);
    }
}

