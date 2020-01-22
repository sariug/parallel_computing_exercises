#include "Matrix.hpp"
#include "MatrixUtils.hpp"
#include <omp.h>
#include <cassert>
#include <cmath>

void test( );

int main()
{
#ifdef PAR_COMP_OMP_ENABLED
#pragma omp parallel
    {
        std::cout <<"hello world from "<< omp_get_thread_num() << '\n'; 
    }
    test();
#else
std::cout << "hello serial world" << '\n'; 
test();
#endif
	return 0;
}




void test()
{

    Matrix A( {{1., 2., 3.},
            {4., 5., 6.},
            {7., 8., 9.},
            {10., 11., 12}} );

    std::vector<double> x{-2., 1., 0.0};


    std::vector<double> y = A*x;


    assert( y.size() == 4 );

    assert( std::abs( y[0] - 0.0 ) < 1e-8 );
    assert( std::abs( y[1] - -3.0 ) < 1e-8 );
    assert( std::abs( y[2] - -6.0 ) < 1e-8 );
    assert( std::abs( y[3] - -9.0 ) < 1e-8 );
}



