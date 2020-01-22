#include "Matrix.hpp"
#include <omp.h>

void test1( );
void test2( );
int main()
{

#pragma omp parallel
    {
        std::cout << omp_get_thread_num() << '\n'; 
    }
	return 0;
}



