#include "Matrix.hpp"
/*
    A simple Matrix class and Utils to manipulate matrices.

	Author: Uğurcan Sarı, Oguz Oztoprak
	Date : 20.11.2019

*/
Matrix::Matrix()
{
    m_matrix = std::vector<std::vector<double>>(3,{0.,0.,0.});
}
Matrix::Matrix(int nRows, int nCols )
{

    m_matrix = std::vector<std::vector<double>>(nRows, std::vector<double>(nCols, 0.0));
}

size_t Matrix::numberOfCols() const
{
    return m_matrix[0].size();
}
size_t Matrix::numberOfRows() const
{
    return m_matrix.size();
}

double& Matrix::operator()(int x, int y)
{
    return m_matrix[x][y];
}

const double& Matrix::operator()(int x, int y) const
{
    return m_matrix[x][y];
}




