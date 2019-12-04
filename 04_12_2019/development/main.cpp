#include "Matrix.hpp"



int main()
{

	Matrix m(3,3);
	m[0][1] = 2;
	m[1][0] = 5;
	m[1][2] = 7.5;
	m[2][2] = 10;
	// output initial matrix

	std::cout << "original matrix:" << std::endl;
	
	for (int i = 0; i < m.numberOfRows(); ++i)
	{
		for (int j = 0; j < m.numberOfCols(); ++j)
		{
			std::cout << m(i, j) << "\t";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	
	// perform addition to itself
	m.operator+=(m);

	std::cout << "new matrix:" << std::endl;

	for (int i = 0; i < m.numberOfRows(); ++i)
	{
		for (int j = 0; j < m.numberOfCols(); ++j)
		{
			std::cout << m(i, j) << "\t";
		}
		std::cout << std::endl;
	}


	return 0;
}