#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

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



