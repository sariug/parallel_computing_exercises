#include "triad_naive.h"
#include <chrono>
#include <iostream>

double triad_naive(double* A, const double* B, const double* C, const double* D, int size, int iter)
{
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < iter; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			A[j] = B[j] + D[j] * C[j];
		}
		if (A[size - 1] > 20) printf("Ai = %f\n", A[size - 1]);
	}
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> ms = end - start;

	return ms.count();
}
