#pragma once

#include <iostream>
#include <vector>
#include <assert.h>

#include "../matrix.h"

namespace utils {
    class MultiplyMatrix {
    public:
        MultiplyMatrix(Matrix *a, Matrix *b);
        Matrix *execute();

    private:
        Matrix *a, *b, *c;
    };
}