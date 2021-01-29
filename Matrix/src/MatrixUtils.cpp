#include "MatrixUtils.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <cmath>
#include <cassert>
#include <limits>
#include <random>
#include <algorithm>
#include <string>
#include <numeric>
/*
    A simple Matrix class and Utils to manipulate matrices.

	Author: Uğurcan Sarı, Oguz Oztoprak
	Date : 20.11.2019

*/
namespace matrixUtilities
{
std::vector<double> solveByGaussElimination( const Matrix& matrix, const std::vector<double>& rhs)
{
    // Fill Gauss Elimination
	std::vector<double> b = rhs;
	std::vector<double> result;
	result.reserve(rhs.size());
	//Assign input matrix
	Matrix A = matrix;

	int n = A.numberOfRows();
	for(int i=0; i<n; i++)
		for(int j=i+1; j<n;j++)
			if (abs(A(i, i) < abs(A(j, i))))
			{
				for (int k = 0; k < n; k++)
				{
					A(i, k) = A(i, k) + A(j, k);
					A(j, k) = A(i, k) - A(j, k);
					A(i, k) = A(i, k) - A(j, k);

				}

				b[i] = b[i] + b[j];
				b[j] = b[i] - b[j];
				b[i] = b[i] - b[j];
			}

	std::cout << A;

	//performing Gaussian elimination
	for(int i=0; i<n;i++)
		for (int j = i + 1; j < n; j++)
		{
			double f = A(j, i) / A(i, i);
			for (int k = 0; k < n; k++)
			{
				A(j, k) = A(j, k) - f * A(i, k);
			}
			b[j] = b[j] - f * b[i];

		}
	//backward substitution
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = i + 1; j < n; ++j)
		{
			b[i] -= (A(i, j)*b[j]);
		}

		b[i] = b[i] / A(i, i);
	}


    return b;
}
Matrix matrixSum(const Matrix &m1, const Matrix &m2)
{
	assert((m1.numberOfRows() == m2.numberOfRows()) & (m1.numberOfCols() == m2.numberOfCols()) && "The size of rows or columns don't match, recheck input matrices");
	size_t size_r = m2.numberOfRows();
	size_t size_c = m2.numberOfCols();

	Matrix mat(size_r, size_c);
	for (size_t i = 0; i < size_r; i++)
		for (size_t j = 0; j < size_c; j++)
			mat(i, j) = m1(i, j) + m2(i, j);

	return mat;
}
//
Matrix matrixSumParallel(const Matrix &m1, const Matrix &m2, int numberOfThreads)
{

	assert((m1.numberOfRows() == m2.numberOfRows()) & (m1.numberOfCols() == m2.numberOfCols()) && "The size of rows or columns don't match, recheck input matrices");
	int size_1 = m1.numberOfCols();
	int size_2 = m1.numberOfRows();
	Matrix sum(m1.numberOfRows(), m1.numberOfCols());
	if (m1.numberOfRows() > m1.numberOfCols())
	{
		size_2 = m1.numberOfCols();
		size_1 = m1.numberOfRows();
	}

	int chunk = size_1 / numberOfThreads;
	// start timer
	std::vector<std::thread> threads;

	// Each Thread gets a specific chunk of the arrays, does the calculation and stores in it sums[i].
	for (int i = 0; i < numberOfThreads - 1; ++i)
	{
		// At each iteration, we create a new thread who gets a function to compute and store the thread in threads vector.
		threads.emplace_back(sumThread, std::ref(m1), std::ref(m2), chunk * i, chunk * (i + 1), size_2, std::ref(sum));
		// NOTE: std::ref(sums[i]) means the sums[i] is passed by reference.
		// https://www.learncpp.com/cpp-tutorial/73-passing-arguments-by-reference/
	}

	// Main thread does the last chunk until the end of the arrays.
	sumThread(m1, m2, (numberOfThreads - 1) * chunk, size_1, size_2, sum);

	// At this point all the calculations is finished, we syncronize the threads( finalize threads ).
	for (auto &thread : threads)
		thread.join();

	// After joining threads we can safely delete the threads, the answer we want is stored inside sums.
	threads.clear();

	return sum;
}
//
Matrix entryWiseProduct(const Matrix &m1, const Matrix &m2)
{
	//checking for rows and columns
	assert((m1.numberOfRows() == m2.numberOfRows()) & (m1.numberOfCols() == m2.numberOfCols()) && "The size of rows or columns don't match, recheck input matrices");
	
	size_t size_r = m2.numberOfRows();
	size_t size_c = m2.numberOfCols();
	Matrix mat(size_r, size_c);
	for (size_t i = 0; i < size_r; i++)
		for (size_t j = 0; j < size_c; j++)
			mat(i, j) = m1(i, j) * m2(i, j);

	return mat;
}


//
Matrix entryWiseProductParallel(const Matrix &m1, const Matrix &m2, int numberOfThreads)
{

	assert((m1.numberOfRows() == m2.numberOfRows()) & (m1.numberOfCols() == m2.numberOfCols()) && "The size of rows or columns don't match, recheck input matrices");

	int size_1 = m1.numberOfCols();
	int size_2 = m1.numberOfRows();
	Matrix product(m1.numberOfRows(), m1.numberOfCols());
	if (m1.numberOfRows() > m1.numberOfCols())
	{
		size_2 = m1.numberOfCols();
		size_1 = m1.numberOfRows();
	}
	int chunk = size_1 / numberOfThreads;
	// start timer
	std::vector<std::thread> threads;

	// Each Thread gets a specific chunk of the arrays, does the calculation and stores in it sums[i].
	for (int i = 0; i < numberOfThreads - 1; ++i)
	{
		// At each iteration, we create a new thread who gets a function to compute and store the thread in threads vector.
		threads.emplace_back(productThread, std::ref(m1), std::ref(m2), chunk * i, chunk * (i + 1), size_2, std::ref(product));
		// NOTE: std::ref(sums[i]) means the sums[i] is passed by reference.
		// https://www.learncpp.com/cpp-tutorial/73-passing-arguments-by-reference/
	}

	// Main thread does the last chunk until the end of the arrays.
	productThread(m1, m2, (numberOfThreads - 1) * chunk, size_1, size_2, product);

	// At this point all the calculations is finished, we syncronize the threads( finalize threads ).
	for (auto &thread : threads)
		thread.join();

	// After joining threads we can safely delete the threads, the answer we want is stored inside sums.
	threads.clear();

	return product;
}

void productThread(const Matrix &m1, const Matrix &m2, int begin, int end, int other_dim, Matrix &m3)
{
	for (size_t i = begin; i < end; i++)
		for (size_t j = 0; j < other_dim; j++)
			m3(i, j) = m1(i, j) * m2(i, j);
}
void sumThread(const Matrix &m1, const Matrix &m2, int begin, int end, int other_dim, Matrix &m3)
{
	for (size_t i = begin; i < end; i++)
		for (size_t j = 0; j < other_dim; j++)
			m3(i, j) = m1(i, j) + m2(i, j);
}
void lu_generator(const Matrix &matrix, Matrix &L, Matrix &U)
{

	const int rows = L.numberOfRows();
	const int cols = L.numberOfCols();
	Matrix A = matrix;

	for (int i = 0; i < rows; i++)
	{
		//Upper triangular matrix
		for (int k = i; k < rows; k++)
		{
			double sum = 0.0;
			for (int j = 0; j < i; j++)
			{
				sum += L(i, j)*U(j, k);
			}

			U(i, k) = A(i, k) - sum;
		}

		//Lower triangular matrix
		for (int k = i; k < rows; k++)
		{
			if (i == k)
				L(i, i) = 1.0;
			else
			{
				double sum = 0.0;
				for (int j = 0; j < i; j++)
					sum += L(k, j)*U(j, i);

				//Evaluating for L
				L(k, i) = (A(k, i) - sum) / U(i, i);

			}

		}



	}


}
void gauss_lu_solver(const Matrix &L, const Matrix &U, std::vector<double>&b)
{
	std::vector<double> z;
	z.resize(b.size());
	b[0] = b[0] / L(0, 0);
	//solve for Ly=z by forward substitution
	for (int i = 1; i < L.numberOfRows(); i++)
	{	
		double sum = 0.0;
		for (int j = 0; j < i; j++)
		{
			sum += L(i, j)*b[j];
		}


		b[i] = (b[i] - sum);
		
	}


	//Solving for Ux=z by backward substitution


	for (int i = L.numberOfRows() - 1; i >= 0; i--)
	{
		for (int j = i+1; j < L.numberOfRows(); ++j)
		{
			b[i] -= (U(i, j)*b[j]);
		}

		b[i] = b[i] / U(i, i);
	}


}
void pad(Matrix &m, int step, double value)
{
	// Can we make something better here ?
	Matrix dummy(m.numberOfRows() + 2 * step, m.numberOfCols() + 2 * step, value);
	for (int i = 0; i < m.numberOfRows(); ++i)
		for (int j = 0; j < m.numberOfCols(); ++j)
			dummy(i + step, j + step) = m(i, j);

	m = dummy;
}
} // namespace matrixUtilities
