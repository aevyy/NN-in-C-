#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <string>

class Matrix {
public:
    Matrix();
    Matrix(int numRows, int numCols, bool isRandom = false);
    
    Matrix transpose() const;
    Matrix duplicate() const;

    // Mutator
    void setValue(int row, int col, double val) { this->values.at(row).at(col) = val; }

    // Accessors
    double getValue(int row, int col) const { return this->values.at(row).at(col); }
    int getNumRows() const { return this->numRows; }
    int getNumCols() const { return this->numCols; }

    // Utility
    void printToConsole() const;
    std::vector<double> toVector() const;

    // Operator Overloads
    Matrix operator*(const Matrix& that) const; // this * that (returns new matrix)
    Matrix& operator*=(const Matrix& that);     // this *= that (modifies this)

private:
    double generateRandomNumber();

    int numRows = 0;
    int numCols = 0;

    // Two dimentional vector: Matrix
    std::vector < std::vector<double> > values;
};