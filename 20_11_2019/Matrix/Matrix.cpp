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

void Matrix::input_matrix()
{
	for (size_t i = 0; i < numberOfRows(); ++i)
		for (size_t j = 0; j < numberOfCols(); ++j)
		{	std::cout << "Element (" << i << "," << j << ") = ";
			std::cin >> operator()(i, j);
			std::cout << "\n";
		}

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



Matrix & Matrix::operator*(Matrix & mat_1)
{
	size_t size_rows = mat_1.numberOfRows();
	size_t size_columns = mat_1.numberOfCols();
	size_t size_r = numberOfRows();
	size_t size_c = numberOfCols();
	//checking for rows and columns
	if (size_rows != size_r && size_columns != size_c)
		throw std::runtime_error("The size of rows or columns don't match, recheck input matrices");

	for (size_t i = 0; i < size_r; i++)
		for (size_t j = 0; j < size_c; j++)
			mat_1(i, j) = mat_1(i, j) * operator()(i, j);

	return mat_1;
}

const double& Matrix::operator()(int x, int y) const
{
    return m_matrix[x][y];
}

Matrix & Matrix::operator+(Matrix & mat_1)
{
	size_t size_rows = mat_1.numberOfRows();
	size_t size_columns = mat_1.numberOfCols();
	size_t size_r = numberOfRows();
	size_t size_c = numberOfCols();
	//checking for rows and columns
	if (size_rows != size_r && size_columns != size_c)
		throw std::runtime_error("The size of rows or columns don't match, recheck input matrices");

	for (size_t i = 0; i < size_r; i++)
		for (size_t j = 0; j < size_c; j++)
			mat_1(i, j) = mat_1(i, j) + operator()(i, j);

	return mat_1;
}

std::ostream & operator<<(std::ostream & os, Matrix & mat_1)
{
	for (size_t i = 0; i < mat_1.numberOfRows(); ++i)
	{
		os << std::endl;
		for (size_t j = 0; j < mat_1.numberOfCols(); ++j)
			os << mat_1.operator()(i, j) << " ";
		
	}
	
	return os;
}
