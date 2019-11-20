#ifndef __MATRIX_UTILS_HPP__
#define __MATRIX_UTILS_HPP__

#include "Matrix.hpp"

namespace matrixUtilities
{
    Matrix matrixSum( const Matrix& m1, const Matrix& m2);
    Matrix matrixSumParallel( const Matrix& m1, const Matrix& m2);
    Matrix entryWiseProduct( const Matrix& m1, const Matrix& m2);
    Matrix entryWiseProductParallel( const Matrix& m1, const Matrix& m2);
}

#endif
