#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <vector>

class Matrix {
public:
    // Constructor
    Matrix(int numRows, int numCols, bool isRandom);
    
    // Function to transpose the matrix
    Matrix *transpose();

    // Function to generate ramdom number
    double generateRandomNumber();
    
    // Setter function where r and c
    // are the indices of row and the column
    // where I want my value v to be set
    void setValue(int r, int c, double v);

    // getter function to get value based on the indices
    double getValue(int r, int c);

    // Getter functions to get num rows and num cols
    int getNumRows() { return this->numRows; }
    int getNumCols() { return this->numCols; }

    // Lets add a function to print the values in the matrix
    void printToConsole();

private:
    // I would like to keep track of
    // number of rows and columns
    int numRows;
    int numCols;

    // Lets create a vector of vectors (which makes it a matrix)
    std::vector < std::vector<double> > values;
};

#endif