/*
	A simple program to benchmark/test norm functions, serial and parallelized.

	Author: Uğurcan Sarı, Oguz Oztoprak
	Date : 06.11.2019

*/

// cout, cin
#include <iostream>

// benchmarking, timing
#include <chrono>

// std::sqrt 
#include <cmath>

// enables assert
#include <cassert>


double norm( double* A, double* B, int size );


void test( );

int main( )
{
    int size;
    std::cout<<"Please enter the length of the array: ";
    std::cin >> size;

    // generate your arrays in heap ( new double[size] )

    // test your norm functions here
    test();

    std::cout << "Test Succeeded!\n";


    auto start = std::chrono::high_resolution_clock::now();
    // Here will be tested in terms of speed

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double,std::milli> duration = end - start;
    std::cout << "Test took " << duration.count() << " ms\n";

    return 0 ;
}

double norm( double* A, double* B, int size )
{
    // write your norm here
    return 1;
}

void test( )
{
    // use assert( )
    // write your test here
}

