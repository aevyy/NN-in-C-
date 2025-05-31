#pragma once

#include <iostream>
#include <vector>
#include <assert.h>

#include "./matrix.h"

namespace utils {
    class multiplyMatrix {
    public:
        multiplyMatrix(Matrix *a, Matrix *b);
        Matrix* execute();

    private:
        Matrix *a, *b, *c;
    };
}