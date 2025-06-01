#pragma once

#include <iostream>
#include <vector>
#include <assert.h>

#include "../Matrix.h"

namespace utils {
    class MatrixToVector {
    public: 
        MatrixToVector(Matrix *a);
        std::vector<double> execute();

    private:
        Matrix *a;
    };
}