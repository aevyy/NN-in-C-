#include "../headers/Matrix.h"

// Default constructor: creates an empty matrix
Matrix::Matrix()
    : numRows(0),
      numCols(0),
      values()
{}

// Constructor: create matrix of given size,
// optionally filled with random values
Matrix::Matrix(int numRows, int numCols, bool isRandom)
    : numRows(numRows), numCols(numCols), values(numRows) { // Initializes outer vector

    // Fill matrix with either random or zero
    for (int i = 0; i < numRows; i++) {
        values[i].resize(numCols);  // Pre-allocates inner vectors

        for (int j = 0; j < numCols; j++) {
            values[i][j] = isRandom ? this->generateRandomNumber() : 0.00;
        }
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

// Matrix Multiplication: this * that (returns new matrix)
Matrix Matrix::operator*(const Matrix& that) const {
    // Are the matrix dimentions eligible for multiplication?
    if (this->numCols != that.numRows) {
        throw std::invalid_argument(
            "Matrix dimensions mismatch for multiplication: " +
            std::to_string(this->numCols) + " != " +
            std::to_string(that.numRows)
        );
    }

    // Result matris
    Matrix result(this->numRows, that.numCols, false);

    // Multiplication
    for (int i = 0; i < this->numRows; i++) {
        for (int k = 0; k < this->numCols; k++) {
            const double a_val = this->values[i][k];    // Cache this value
            for (int j = 0; j < that.numCols; j++) {
                // Accumulating product directly into result
                result.values[i][j] += a_val * that.values[k][j];
            }
        }
    }

    return result;
}

// Compound assignment: this += that (modifies this matrix)
Matrix& Matrix::operator*=(const Matrix& that) {
    *this = *this * that;   /// Reuse operator*
    return *this;
}

// to vector
std::vector<double> Matrix::toVector() const {
    std::vector<double>result;
    result.reserve(numRows * numCols);  // Pre-allocation for efficiency

    for (const auto& row : values) {    // Outer loop (rows)
        for (double val : row) {        // Inner loop (values in row)
            result.push_back(val);
        }
    }
    return result;
}