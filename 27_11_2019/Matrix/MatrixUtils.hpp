#ifndef __MATRIX_UTILS_HPP__
#define __MATRIX_UTILS_HPP__

#include "Matrix.hpp"
/*
    A simple Matrix class and Utils to manipulate matrices.

	Author: Uğurcan Sarı, Oguz Oztoprak
	Date : 20.11.2019

*/
namespace matrixUtilities
{
    Matrix matrixSum( const Matrix& m1, const Matrix& m2);
    Matrix matrixSumParallel( const Matrix& m1, const Matrix& m2, int numberOfThreads);
    Matrix entryWiseProduct( const Matrix& m1, const Matrix& m2);
    Matrix entryWiseProductParallel( const Matrix& m1, const Matrix& m2, int numberOfThreads);
	void productThread(Matrix & m1, Matrix & m2, int begin, int end, int other_dim, Matrix & m3);
	void check(const Matrix& m1, const Matrix& m2);
	void sumThread(Matrix & m1, Matrix & m2, int begin, int end, int other_dim, Matrix & m3);
	//additional functions
	
}

#endif
