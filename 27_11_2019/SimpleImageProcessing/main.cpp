#include "MatrixUtils.hpp"
#include "ppImageUtils.hpp"
#include "Matrix.hpp"

/*
    Main file to process image

	Author: Uğurcan Sarı, Oguz Oztoprak
	Date : 20.11.2019

*/




int main()
{
	test();
	int number_of_threads;
	std::cout << "Enter the number of threads: \n";
	std::cin >> number_of_threads;

   auto m = imageProcessing::read_image("l.pgm");

	auto size_rows = m.numberOfRows();
	std::cout << size_rows << "\n";
	auto size_col = m.numberOfCols();
	check(m);
		//!!!NECESSARY TO INCREASE THE MATRIX SIZE TO GET APPROPRIATE RESULT
	// Also can call increase inside every function, can be done as pleased
	increase(m);

	Matrix m_0 = cross_wise_parallel_masked_image_generator(m, imageProcessing::masks::blur,number_of_threads);
	Matrix m_1 = cross_wise_parallel_masked_image_generator(m, imageProcessing::masks::edge_detection, number_of_threads);
	Matrix m_2 = cross_wise_parallel_masked_image_generator(m, imageProcessing::masks::sharpen, number_of_threads);
	
	imageProcessing::write_image("m_parallel.pgm", m_0);
	imageProcessing::write_image("m1_parallel.pgm", m_1);
	imageProcessing::write_image("m2_parallel.pgm", m_2);
    
	return 0;
}

