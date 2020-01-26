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
	imageProcessing::test_image_processing_methods();
	int number_of_threads;
	std::cout << "Enter the number of threads: \n";
	std::cin >> number_of_threads;

	auto m = imageProcessing::read_image("l.pgm");
	matrixUtilities::pad(m);
	Matrix m_0 = imageProcessing::apply_mask_to_image(m, imageProcessing::masks::blur, imageProcessing::CalculationMethod::Serial);
	Matrix m_1 = imageProcessing::apply_mask_to_image(m, imageProcessing::masks::edge_detection, imageProcessing::CalculationMethod::ParallelRowwise, number_of_threads);
	Matrix m_2 = imageProcessing::apply_mask_to_image(m_0, imageProcessing::masks::edge_detection, imageProcessing::CalculationMethod::ParallelColumnwise, number_of_threads);
	Matrix m_3 = imageProcessing::apply_mask_to_image(m_0, imageProcessing::masks::sharpen, imageProcessing::CalculationMethod::ParallelCross, number_of_threads);

	imageProcessing::write_image("m0_blurred_serial.pgm", m_0);
	imageProcessing::write_image("m1_edge_rowwise.pgm", m_1);
	imageProcessing::write_image("m2_edge_columnwise.pgm", m_2);
	imageProcessing::write_image("m3_sharpen_cross.pgm", m_3);

	return 0;
}

