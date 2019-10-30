/*
	A simple program to find a number using threads library.

	Author: Uğurcan Sarı, Oğuz Öztoprak
	Date : 30.10.2019

*/
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

/*	 	
*	Function to find the password. If the password is equal to 
*	counter, then the reference value is changed.
*/
void find_pass(int min, int max, int &pass, const int real_pass)
{
	for (int i = min; i <= max; i++)
	{
		if (i == real_pass)
			pass = real_pass;
	}
}

int main()
{
	const int max_pass = 10000;	// Maxımum password we allow
	int real_pass = 8952;		// The real password
	int numberOfThreads = 2;	// Number of threads
	int npt = max_pass / numberOfThreads;	// Number of numbers per thread
	std::vector<int> pass_container(numberOfThreads, -1);	// Passwords to hold with -1 initialization

	// Create vector of threads
	std::vector<std::thread> v;

	for (int i = 0; i < numberOfThreads; ++i)
	{
		v.emplace_back(find_pass,
					   npt * i,
					   (npt * i + npt > max_pass) ? max_pass : npt * i + npt,
					   std::ref(pass_container[i]), real_pass);
	}
	// Join them
	for (std::thread &t : v)
	{
		t.join();
	}
	v.clear();
	for (int i = 0; i<numberOfThreads; i++)
	{
		if(pass_container[i]!=-1)
			std::cout<<"The password is "<<pass_container[i]<<" and was at the thread "<<i<<std::endl;
	}
	return 0;
}
