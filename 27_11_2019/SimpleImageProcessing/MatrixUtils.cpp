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
	size_t size_rows = m1.numberOfRows();
	size_t size_columns = m1.numberOfCols();
	size_t size_r = m2.numberOfRows();
	size_t size_c = m2.numberOfCols();
	//checking for rows and columns
	if (size_rows != size_r && size_columns != size_c)
		throw std::runtime_error("The size of rows or columns don't match, recheck input matrices");

	Matrix mat(size_r, size_c);
	for (size_t i = 0; i < size_r; i++)
		for (size_t j = 0; j < size_c; j++)
			mat(i, j) = m1(i, j) + m2(i, j);

	return mat;
}
//
Matrix matrixSumParallel(const Matrix &m1, const Matrix &m2, int numberOfThreads)
{

	Matrix A = m1;
	Matrix B = m2;
	check(A, B);
	int size_1 = 0;
	int size_2 = 0;
	Matrix sum(A.numberOfRows(), A.numberOfCols());
	if (A.numberOfRows() > A.numberOfCols())
	{
		size_2 = A.numberOfCols();
		size_1 = A.numberOfRows();
	}
	else
	{
		size_1 = A.numberOfCols();
		size_2 = A.numberOfRows();
	}
	int chunk = size_1 / numberOfThreads;
	// start timer
	std::vector<std::thread> threads;

	// Each Thread gets a specific chunk of the arrays, does the calculation and stores in it sums[i].
	for (int i = 0; i < numberOfThreads - 1; ++i)
	{
		// At each iteration, we create a new thread who gets a function to compute and store the thread in threads vector.
		threads.emplace_back(sumThread, std::ref(A), std::ref(B), chunk * i, chunk * (i + 1), size_2, std::ref(sum));
		// NOTE: std::ref(sums[i]) means the sums[i] is passed by reference.
		// https://www.learncpp.com/cpp-tutorial/73-passing-arguments-by-reference/
	}

	// Main thread does the last chunk until the end of the arrays.
	sumThread(A, B, (numberOfThreads - 1) * chunk, size_1, size_2, sum);

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
	size_t size_rows = m1.numberOfRows();
	size_t size_columns = m1.numberOfCols();
	size_t size_r = m2.numberOfRows();
	size_t size_c = m2.numberOfCols();
	//checking for rows and columns
	if (size_rows != size_r && size_columns != size_c)
		throw std::runtime_error("The size of rows or columns don't match, recheck input matrices");
	Matrix mat(size_r, size_c);
	for (size_t i = 0; i < size_r; i++)
		for (size_t j = 0; j < size_c; j++)
			mat(i, j) = m1(i, j) * m2(i, j);

	return mat;
}
void check(const Matrix &m1, const Matrix &m2)
{
	size_t size_rows = m1.numberOfRows();
	size_t size_columns = m1.numberOfCols();
	size_t size_r = m2.numberOfRows();
	size_t size_c = m2.numberOfCols();
	//checking for rows and columns
	if (size_rows != size_r && size_columns != size_c)
		throw std::runtime_error("The size of rows or columns don't match, recheck input matrices");
}

void sumThread(Matrix &m1, Matrix &m2, int begin, int end, int other_dim, Matrix &m3)
{
	for (size_t i = begin; i < end; i++)
		for (size_t j = 0; j < other_dim; j++)
			m3(i, j) = m1(i, j) + m2(i, j);
}
//
Matrix entryWiseProductParallel(const Matrix &m1, const Matrix &m2, int numberOfThreads)
{

	Matrix A = m1;
	Matrix B = m2;
	check(A, B);
	int size_1 = 0;
	int size_2 = 0;
	Matrix product(A.numberOfRows(), A.numberOfCols());
	if (A.numberOfRows() > A.numberOfCols())
	{
		size_2 = A.numberOfCols();
		size_1 = A.numberOfRows();
	}
	else
	{
		size_1 = A.numberOfCols();
		size_2 = A.numberOfRows();
	}
	int chunk = size_1 / numberOfThreads;
	// start timer
	std::vector<std::thread> threads;

	// Each Thread gets a specific chunk of the arrays, does the calculation and stores in it sums[i].
	for (int i = 0; i < numberOfThreads - 1; ++i)
	{
		// At each iteration, we create a new thread who gets a function to compute and store the thread in threads vector.
		threads.emplace_back(productThread, std::ref(A), std::ref(B), chunk * i, chunk * (i + 1), size_2, std::ref(product));
		// NOTE: std::ref(sums[i]) means the sums[i] is passed by reference.
		// https://www.learncpp.com/cpp-tutorial/73-passing-arguments-by-reference/
	}

	// Main thread does the last chunk until the end of the arrays.
	productThread(A, B, (numberOfThreads - 1) * chunk, size_1, size_2, product);

	// At this point all the calculations is finished, we syncronize the threads( finalize threads ).
	for (auto &thread : threads)
		thread.join();

	// After joining threads we can safely delete the threads, the answer we want is stored inside sums.
	threads.clear();

	return product;
}

void productThread(Matrix &m1, Matrix &m2, int begin, int end, int other_dim, Matrix &m3)
{
	for (size_t i = begin; i < end; i++)
		for (size_t j = 0; j < other_dim; j++)
			m3(i, j) = m1(i, j) * m2(i, j);
}
} // namespace matrixUtilities
