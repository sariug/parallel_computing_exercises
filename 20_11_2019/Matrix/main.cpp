#include "Matrix.hpp"
#include "MatrixUtils.hpp"
//#include <cstdio>
#include <cassert>
#include <chrono>
#include <random>
#define getName(var) #var
/*
    A simple Matrix class and Utils to manipulate matrices.

	Author: Uğurcan Sarı, Oguz Oztoprak
	Date : 20.11.2019

*/


void test_all();
void test_randomized_sum( size_t test_size, int number_of_threads );
void test_randomized_multiply( size_t test_size, int number_of_threads );

int main()
{

	test_all();
	test_randomized_sum(9000, 6);
    test_randomized_multiply(9000,6);



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
void test_randomized_sum( size_t test_size, int number_of_threads )
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(1.0, 100.0);


    Matrix A(test_size, test_size); 
    Matrix B(test_size, test_size); 

    for ( size_t i = 0 ; i < test_size ; ++i )
    {
        for ( size_t j = 0 ; j < test_size ; ++j )
        {
            A(i,j) = dis(gen);
            B(i,j) = dis(gen);
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    Matrix random_test_serial_result = matrixUtilities::matrixSum(A, B );
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> duration = end - start;
	std::cout << "Sum Test serial took " << duration.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    Matrix random_test_result_parallel = matrixUtilities::matrixSumParallel(A, B, number_of_threads );

	end = std::chrono::high_resolution_clock::now();

	duration = end - start;
	std::cout << "Sum Test parallel took " << duration.count() << " ms\n";

    assert( random_test_serial_result == random_test_result_parallel );



}
void test_randomized_multiply( size_t test_size, int number_of_threads )
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(1.0, 100.0);

    Matrix A(test_size, test_size); 
    Matrix B(test_size, test_size); 

    for ( size_t i = 0 ; i < test_size ; ++i )
    {
        for ( size_t j = 0 ; j < test_size ; ++j )
        {
            A(i,j) = dis(gen);
            B(i,j) = dis(gen);
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    Matrix random_test_mul_serial_result = matrixUtilities::entryWiseProduct(A, B );
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> duration = end - start;
	std::cout << "Sum Test serial took " << duration.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    Matrix random_test_mul_result_parallel = matrixUtilities::entryWiseProductParallel(A, B, number_of_threads );
	end = std::chrono::high_resolution_clock::now();

	duration = end - start;
	std::cout << "Sum Test parallel took " << duration.count() << " ms\n";

    assert( random_test_mul_serial_result == random_test_mul_result_parallel );

}
