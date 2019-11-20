#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__
/*
    A simple Matrix class and Utils to manipulate matrices.

	Author: Uğurcan Sarı, Oguz Oztoprak
	Date : 20.11.2019

*/
#include <iostream>
#include <vector>

class Matrix
{
    public:
        Matrix( );
        Matrix( int nRows, int nCols );

        size_t numberOfCols( );
        size_t numberOfRows( );

        double& operator()(int x, int y);


    private:
        std::vector< std::vector< double > > m_matrix;
};

#endif


