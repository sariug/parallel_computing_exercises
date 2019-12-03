#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__
/*
    A simple Matrix class and Utils to manipulate matrices.

	Author: Uğurcan Sarı, Oguz Oztoprak
	Date : 20.11.2019

*/
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

class Matrix
{
    public:
        Matrix( );
        Matrix( int nRows, int nCols );
		void input_matrix();

        size_t numberOfCols( ) const;
        size_t numberOfRows( ) const;

        double& operator()(int x, int y);
        friend bool operator==(const Matrix& lhs, const Matrix& rhs);
		Matrix& operator + (Matrix& mat_1);
		Matrix& operator *(Matrix& mat_1);

	    const double& operator()(int x, int y) const;
	    friend std::ostream& operator<<(std::ostream &os, Matrix& mat_1);
    private:
        std::vector< std::vector< double > > m_matrix;
};

#endif



