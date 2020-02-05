#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__
/*
    A simple Matrix class and Utils to manipulate matrices.

	Author: Uğurcan Sarı, Oguz Oztoprak, Dharmin Shah
	Date : 27.11.2019

*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
#include <stdexcept>
#include <cassert>

class Matrix
{
public:
    Matrix();
    Matrix(int nRows, int nCols);

    Matrix(int nRows, int nCols, double value);
    Matrix(std::vector<std::vector<double>> m);
    void input_matrix();

    size_t numberOfCols() const;
    size_t numberOfRows() const;

    std::vector<double> sliceAndSerialsRows(size_t begin, size_t end);
    double &operator()(int x, int y);
    friend bool operator==(const Matrix &lhs, const Matrix &rhs);
    Matrix &operator+(Matrix &mat_1);
    Matrix &operator+=(const Matrix &mat_1);
    Matrix &operator*(Matrix &mat_1);
    std::vector<double> &operator[](int index);
    const double &operator()(int x, int y) const;

    std::vector<double> operator*( const std::vector<double>& );

    // Check functions
    bool checkMinimumNumOfRowsAndCols(size_t);

    friend std::ostream &operator<<(std::ostream &os, Matrix &mat_1);

private:
    std::vector<std::vector<double>> m_matrix;
};

#endif
