#include "Matrix.hpp"
#include "MatrixUtils.hpp"

#include <cassert>

void testSolve( );

int main( )
{
    testSolve( );

    return 0;
}
void testSolve( )
{
    Matrix A( 3, 3 );

    A( 0, 0 ) = 3.0;
    A( 0, 1 ) = 2.0;
    A( 0, 2 ) = -4.0;

    A( 1, 0 ) = 2.0;
    A( 1, 1 ) = 3.0;
    A( 1, 2 ) = 3.0;

    A( 2, 0 ) = 5.0;
    A( 2, 1 ) = -3.0;
    A( 2, 2 ) = 1.0;

    std::vector<double> rhs = {3., 15., 14.};

    std::vector<double> answer = matrixUtilities::solveByGaussElimination( A, rhs );

    assert( answer.size() == 3 );
    assert( std::abs( answer[0] - 3.0 ) < std::numeric_limits<double>::epsilon( ) );
    assert( std::abs( answer[0] - 3.0 ) < std::numeric_limits<double>::epsilon( ) );
    assert( std::abs( answer[1] - 1.0 ) < std::numeric_limits<double>::epsilon( ) );
}
