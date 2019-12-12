#include "Matrix.hpp"
#include "MatrixUtils.hpp"
#include<iostream>
#include <cassert>
#include<typeinfo>

void testSolve( );

int main( )
{
    testSolve( );

    return 0;
}
void testSolve( )
{
    Matrix A( 3, 3 );
	//A( 0, 0 ) = 1.0;
	//A( 0, 1 ) = 2.0;
	//A( 0, 2 ) = -1.0;

	//A( 1, 0 ) = 4.0;
	//A( 1, 1 ) = 3.0;
	//A( 1, 2 ) = 1.0;

	//A( 2, 0 ) = 2.0;
	//A( 2, 1 ) = 2.0;
	//A( 2, 2 ) = 3.0;
    A( 0, 0 ) = 3.0;
    A( 0, 1 ) = 2.0;
    A( 0, 2 ) = -4.0;

    A( 1, 0 ) = 2.0;
    A( 1, 1 ) = 3.0;
    A( 1, 2 ) = 3.0;

    A( 2, 0 ) = 5.0;
    A( 2, 1 ) = -3.0;
    A( 2, 2 ) = 1.0;

	std::cout << A;
    std::vector<double> rhs = {3.0, 15.0, 14.0};

    std::vector<double> answer = matrixUtilities::solveByGaussElimination( A, rhs );

    assert( answer.size() == 3 );
	double eps = 1e-10;
	//the numeric limits are of order 1e-16 so the assert will not work.
    assert( std::abs( answer[0] - 3.0 ) < eps );
    assert( std::abs( answer[1] - 1.0 ) < eps );
    assert( std::abs( answer[2] - 2.0 ) < eps );
}
