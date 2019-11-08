#include <iostream>
#include <chrono>
#include <cmath>
#include <cassert>
#include <limits>
#include <random>
#include <algorithm>
#include <string>
#include <thread>
#include <numeric>
/*
	An example of using threads to calculate the so-called norm(ish) function.

	Author: Uğurcan Sarı, Oguz Oztoprak
	Date : 06.11.2019

*/


void normThread(double* A, double* B,  int size, int start, int end, double& sum)
{
    double local_sum = 0.0;

    for (int i = start; i < end; ++i )
    {
        local_sum += A[i] * B[i];
    }
    sum = local_sum;

}

int main()
{
    int size;
    std::cout<<"Please enter the length of the array: ";
    std::cin >> size;
      
    int numberOfThreads = 6;

    int chunk = size / 6;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(1.0, 1000.0);

    // Create and fill the arrays
    double* A = new double[size];
    double* B = new double[size];
    for (int n = 0; n < size; ++n) 
    {
        A[n] = dis(gen);
        B[n] = dis(gen);
    }
    // start timer
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<double> sums(numberOfThreads, 0.0);

    std::vector<std::thread> threads;

    for(int i = 0; i < numberOfThreads-1 ; ++i )
    {
        threads.emplace_back(normThread, A, B, size, chunk*i, chunk * (i+1), std::ref(sums[i]));  
    }

    normThread(A,B,size, (numberOfThreads-1)*chunk, size, sums[numberOfThreads-1]); 


    for(auto& thread : threads ) thread.join();
    threads.clear();

    std::cout <<"\nCalculated value with my function : ";
    std::cout << std::sqrt(std::accumulate(sums.begin(), sums.end(), 0.0) )<<'\n';
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double,std::milli> duration = end - start;
    std::cout <<"Test using threads took " << duration.count() << " ms\n";

    std::cout <<"\nReference value : ";
    start = std::chrono::high_resolution_clock::now();
    std::cout <<std::sqrt(std::inner_product(A, A+size, B, 0.0) );
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout <<"\nReference test took " << duration.count() << " ms\n";
    return 0;
}
