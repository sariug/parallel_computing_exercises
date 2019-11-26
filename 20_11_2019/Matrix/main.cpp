#include "Matrix.hpp"
#include "MatrixUtils.hpp"
#include <stdio.h>
#include<assert.h>
#define getName(var) #var
/*
    A simple Matrix class and Utils to manipulate matrices.

	Author: Uğurcan Sarı, Oguz Oztoprak
	Date : 20.11.2019

*/


void test_all();

int main()
{
	test_all();
	//printf("%s", getName(S));
	//std::cout << "= "<<S;


	system("pause");

    return 0;
}

void test_all()
{

	Matrix A(5, 4);

	Matrix B(5, 4);

	for (size_t i = 0; i < A.numberOfRows(); ++i)
		for (size_t j = 0; j < A.numberOfCols(); ++j)
			A(i, j) = 5;

	for (size_t i = 0; i < B.numberOfRows(); ++i)
		for (size_t j = 0; j < B.numberOfCols(); ++j)
			B(i, j) = 6;


	Matrix test_sum = matrixUtilities::matrixSum(A, B);
	Matrix test_product = matrixUtilities::entryWiseProduct(A, B);
	Matrix test_sum_parallel = matrixUtilities::matrixSumParallel(A, B, 2);
	Matrix test_product_parallel = matrixUtilities::entryWiseProductParallel(A, B, 2);
	for (int i = 0; i < test_sum.numberOfRows(); ++i)
		for (int j = 0; j < test_sum.numberOfCols(); ++j)
		{
			assert(test_sum(i, j) == 11);
			assert(test_product(i, j) == 30);
			assert(test_sum_parallel(i, j) == 11);
			assert(test_product_parallel(i, j) == 30);
		}

	std::cout << "All tests passed successfully.\n";


}
