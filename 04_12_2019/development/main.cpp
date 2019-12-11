#include "Matrix.hpp"



int main()
{
    size_t nRows_m1 = 5;
    size_t nColumns_m1 = 8;

    size_t nRows_m2 = 5;
    size_t nColumns_m2 = 6;

    // create instance of class Matrix
	Matrix m1(nRows_m1, nColumns_m1);
    Matrix m2(nRows_m2, nColumns_m2);

    // assign values to matrix m1
    for(int i = 0; i < nRows_m1; i++)
    {
        for(int j = 0; j < nColumns_m1; j++)
        {
            m1[i][j] = i * 2 - j % 5;
        }
    }

    // assign values to matrix m2
    for(int i = 0; i < nRows_m2; i++)
    {
        for(int j = 0; j < nColumns_m2; j++)
        {
            m2[i][j] = i * 4 - j % 2;
        }
    }

	// output initial matrices

	std::cout << "original matrix m1:" << std::endl;
    std::cout << m1 << std::endl;

    std::cout << "original matrix m2:" << std::endl;
    std::cout << m2 << std::endl;
	
	// perform addition to itself and output

    m1 += m1;
    std::cout << "m1 + m1:" << std::endl;
    std::cout << m1 << std::endl;

    // use a try catch block because m1 and m2 aren't necessarily the same size
    try {
        m1+=m2;
        std::cout << "m1 + m2:" << std::endl;
        std::cout << m1 << std::endl;
    }
    catch (const char* msg)
    {
        std::cout << msg << std::endl;
    }

    m2+=m2;
    std::cout << "m2 + m2:" << std::endl;
    std::cout << m2 << std::endl;

	return 0;
}