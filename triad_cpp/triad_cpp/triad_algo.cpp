#include "triad_algo.h"
#include <chrono>
#include <algorithm>
#include <numeric>
#include <iostream>

double triad_algo(std::vector<double>& A, const std::vector<double>& B, const std::vector<double>& C, const std::vector<double>& D, int iter)
{
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < iter; ++i)
	{
		//std::transform(C.begin(), C.end(), D.begin(), std::multiplies<>());
		for (int j = 0; j < A.size(); ++j)
		{
			A[j] = B[j] + D[j] * C[j];
		}
		if (A[A.size() - 1] > 20) printf("Ai = %f\n", A[A.size() - 1]);
	}
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> ms = end - start;

	return ms.count();
}
