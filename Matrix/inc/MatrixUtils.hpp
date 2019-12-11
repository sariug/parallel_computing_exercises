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
	void pad(Matrix & m,int step=1, double value=0.0);
	void productThread(const Matrix & m1, const Matrix & m2, int begin, int end, int other_dim, Matrix & m3);
	void sumThread(const Matrix & m1, const Matrix & m2, int begin, int end, int other_dim, Matrix & m3);
    std::vector<double> solveByGaussElimination( const Matrix& matrix, const std::vector<double>& rhs);
	//additional functions
	
}

#endif
