#include "Matrix.hpp"
/*
    A simple Matrix class and Utils to manipulate matrices.

	Author: Uğurcan Sarı, Oguz Oztoprak
	Date : 20.11.2019

*/
Matrix::Matrix()
{
	m_matrix = std::vector<std::vector<double>>(3, {0., 0., 0.});
}
Matrix::Matrix(int nRows, int nCols)
{

	m_matrix = std::vector<std::vector<double>>(nRows, std::vector<double>(nCols, 0.0));
}

Matrix::Matrix(int nRows, int nCols, double value)
{

	m_matrix = std::vector<std::vector<double>>(nRows, std::vector<double>(nCols, value));
}

Matrix::Matrix(std::vector<std::vector<double>> m):m_matrix(m){}

bool operator==(const Matrix &lhs, const Matrix &rhs)
{
	size_t number_of_rows = rhs.numberOfRows();
	size_t number_of_cols = rhs.numberOfCols();

	for (size_t i = 0; i < number_of_rows; ++i)
	{
		for (size_t j = 0; j < number_of_cols; ++j)
		{
			if (std::abs(lhs(i, j) - rhs(i, j)) > std::numeric_limits<double>::epsilon())
				return false;
		}
	}
	return true;
}

void Matrix::input_matrix()
{
	for (size_t i = 0; i < numberOfRows(); ++i)
		for (size_t j = 0; j < numberOfCols(); ++j)
		{
			std::cout << "Element (" << i << "," << j << ") = ";
			std::cin >> operator()(i, j);
			std::cout << "\n";
		}
	std::cout << "\n";
}

size_t Matrix::numberOfCols() const
{
	return m_matrix[0].size();
}
size_t Matrix::numberOfRows() const
{
	return m_matrix.size();
}

double &Matrix::operator()(int x, int y)
{
	return m_matrix[x][y];
}

Matrix &Matrix::operator*(Matrix &mat_1)
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

const double &Matrix::operator()(int x, int y) const
{
	return m_matrix[x][y];
}

Matrix &Matrix::operator+(Matrix &mat_1)
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

Matrix &Matrix::operator+=(const Matrix &mat_1)
{
	size_t nRows = numberOfRows();
	size_t nColumns = numberOfCols();

	// throw an exception if matrix dimensions do not match
	if ( nRows != mat_1.numberOfRows() || nColumns != mat_1.numberOfCols())
    {
	    throw "invalid entry. matrix dimensions do not match!";
    }

	for (int i = 0; i < nRows; ++i)
	{
		for (int j = 0; j < nColumns; ++j)
		{
			m_matrix[i][j] += mat_1(i, j);
		}
	}
	
	return *this;
}


std::ostream &operator<<(std::ostream &os, Matrix &mat_1)
{
	for (size_t i = 0; i < mat_1.numberOfRows(); ++i)
	{
		os << std::endl;
		for (size_t j = 0; j < mat_1.numberOfCols(); ++j)
			os << mat_1(i, j) << " ";
	}
	std::cout << "\n";

	return os;
}
std::vector<double> &Matrix::operator[](int index)
{
	return m_matrix[index];
}

bool Matrix::checkMinimumNumOfRowsAndCols(int n)
{
	if (this->numberOfCols() < n || this->numberOfRows() < n)
		throw std::runtime_error("Minimum rows or columns should be %d" + std::to_string(n) + ", check input matrix");
}
