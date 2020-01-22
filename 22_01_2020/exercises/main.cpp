#include "Matrix.hpp"
#include <omp.h>

void test1( );
void test2( );
int main()
{
#ifdef PAR_COMP_OMP_ENABLED
#pragma omp parallel
    {
        std::cout << omp_get_thread_num() << '\n'; 
    }
#else
std::cout << "hello world" << '\n'; 
#endif
	return 0;
}



