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


void normThread(double* A, double* B, int start, int end, double& sum)
{
    double local_sum = 0.0;

    for (int i = start; i < end; ++i )
    {
        local_sum += A[i] * B[i];
    }
    // Notice sum is passed by reference!!
    sum = local_sum;

}

int main( )
{
    int size;
    std::cout<<"Please enter the length of the array: ";
    std::cin >> size;
      
    int numberOfThreads;
    std::cout<<"Please enter number of threads you want to spawn : ";
    std::cin >> numberOfThreads;

    int chunk = size / numberOfThreads;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(1.0, 100.0);

    // Create and fill the arrays.
    double* A = new double[size];
    double* B = new double[size];
    
    // Fill the arrays with random numbers.
    for (int n = 0; n < size; ++n) 
    {
        A[n] = dis(gen);
        B[n] = dis(gen);
    }

    // start timer
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<double> sums(numberOfThreads, 0.0);

    std::vector<std::thread> threads;

    // Each Thread gets a specific chunk of the arrays, does the calculation and stores in it sums[i].
    for(int i = 0; i < numberOfThreads-1 ; ++i )
    {
        // At each iteration, we create a new thread who gets a function to compute and store the thread in threads vector.
        threads.emplace_back(normThread, A, B, chunk*i, chunk * (i+1), std::ref(sums[i]));  
        // NOTE: std::ref(sums[i]) means the sums[i] is passed by reference.
        // https://www.learncpp.com/cpp-tutorial/73-passing-arguments-by-reference/
    }

    // Main thread does the last chunk until the end of the arrays.
    normThread(A,B, (numberOfThreads-1)*chunk, size, sums[numberOfThreads-1]); 


    // At this point all the calculations is finished, we syncronize the threads( finalize threads ).
    for(auto& thread : threads ) thread.join();

    // After joining threads we can safely delete the threads, the answer we want is stored inside sums.
    threads.clear();

    std::cout <<"\nCalculated value with my function : ";
    

    // Accumulate sums up a container given a range. We sum up all local sums and take the square root.
    std::cout << std::sqrt(std::accumulate(sums.begin(), sums.end(), 0.0) )<<'\n';


    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double,std::milli> duration = end - start;
    std::cout <<"Test using threads took " << duration.count() << " ms\n";

    std::cout <<"\nReference value : ";
    start = std::chrono::high_resolution_clock::now();

    
    // Again our reference implementation using standard inner_product function.
    std::cout <<std::sqrt(std::inner_product(A, A+size, B, 0.0) );


    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout <<"\nReference test took " << duration.count() << " ms\n";
    return 0;
}
