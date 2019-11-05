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


// Fill
double norm(double* A, double* B, size_t size)
{
    double sum = 0.0;
    for (size_t i = 0; i < size; ++i )
    {
        sum += A[i] * B[i];
    }

    return std::sqrt(sum); 
}

void normThread(double* A, double* B,  int size, int start, int end, double& sum)
{
    double local_sum = 0.0;

    for (int i = start; i < end; ++i )
    {
        local_sum += A[i] * B[i];
    }
    sum = local_sum;

}

void randomizedTest( size_t );
void randomizedTest2( size_t );
int main()
{
    int size;
    
    std::cin >> size;

    //randomizedTest(static_cast<size_t>(size));
    
    int numberOfThreads = 6;

    int chunk = size / 6;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(1.0, 1000.0);

    
    double* A = new double[size];
    double* B = new double[size];
    for (int n = 0; n < size; ++n) 
    {
        A[n] = dis(gen);
        B[n] = dis(gen);
    }
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


    std::cout << std::sqrt(std::accumulate(sums.begin(), sums.end(), 0.0) )<<'\n';
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double,std::milli> duration = end - start;
    std::cout <<"threaded took " << duration.count() << " ms\n";

    std::cout <<"ref : \n";
    start = std::chrono::high_resolution_clock::now();
    std::cout <<std::sqrt(std::inner_product(A, A+size, B, 0.0) );
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout <<"Ref took " << duration.count() << " ms\n";
    return 0;

}

void randomizedTest( size_t my_size)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(1.0, 1000.0);

    
    double* A = new double[my_size];
    double* B = new double[my_size];
    for (size_t n = 0; n < my_size; ++n) 
    {
        A[n] = dis(gen);
        B[n] = dis(gen);
    }

    auto start = std::chrono::high_resolution_clock::now();
    double normAns = norm(A,B,my_size);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double,std::milli> duration = end - start;
    double mflopSeconds = (2*my_size)* 1e-6 / (duration.count() * 1e-3) ;
    std::cout <<"Test took " << duration.count() << " ms\n";
    std::cout <<"MFLOP/s " << mflopSeconds<<'\n';
    std::cout <<"answer: " << normAns << '\n';
    start = std::chrono::high_resolution_clock::now();
    normAns =  std::sqrt( std::inner_product(A,A+my_size, B,0.0)); 
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    mflopSeconds = (2*my_size)* 1e-6 / (duration.count() * 1e-3) ;
    std::cout << "reference\n";
    std::cout <<"Test took " << duration.count() << " ms\n";
    std::cout <<"answer: " << normAns << '\n';
    std::cout <<"MFLOP/s " << mflopSeconds<<'\n';

}
void randomizedTest2( size_t my_size)
{
    double* A = new double[my_size];
    double* B = new double[my_size];
    for (size_t n = 0; n < my_size; ++n) 
    {
        A[n] = 2.;
        B[n] = 3.;
    }

    auto start = std::chrono::high_resolution_clock::now();
    double normAns = norm(A,B,my_size);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double,std::milli> duration = end - start;
    std::cout <<"Test took " << duration.count() << " ms\n";
    std::cout <<"answer: " << normAns << '\n';
    assert( normAns == std::sqrt( std::inner_product(A, A + my_size, B, 0.0)) );

}
