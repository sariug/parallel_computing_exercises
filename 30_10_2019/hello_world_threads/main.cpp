/*
	A simple program to find a number using threads library.

	Author: Uğurcan Sarı, Oguz Oztoprak
	Date : 30.10.2019

*/
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>



void thread(int i)
{
	std::cout <<"thread :" << i <<" says hello\n";
	std::this_thread::sleep_for(std::chrono::seconds(1));
}


int main()
{
	int numberOfThreads = 2;
	std::vector<std::thread> v;
	for (int i = 0; i < numberOfThreads; ++i)
	{
		v.emplace_back(thread, i);
	}
	for (std::thread & t : v) {
		t.join();
	}
	v.clear();
	return 0;
}
