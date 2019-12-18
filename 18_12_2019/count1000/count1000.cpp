#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
int my_count = 0;
std::mutex my_count_mutex;

void count()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    my_count_mutex.lock();
    my_count++;
    my_count_mutex.unlock();
}

int main()
{

    std::vector<std::thread> threads;

    for (int i = 0; i < 1000; ++i)
        threads.emplace_back(count);
	for (auto &thread : threads)
		thread.join();
    std::cout << "We counted until " << my_count << "." << std::endl;
    return 0;
}
