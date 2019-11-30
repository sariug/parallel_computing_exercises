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
