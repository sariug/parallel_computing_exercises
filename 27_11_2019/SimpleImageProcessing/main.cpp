#include "MatrixUtils.hpp"
#include "ppImageUtils.hpp"
/*
    Main file to process image

	Author: Uğurcan Sarı, Oguz Oztoprak
	Date : 20.11.2019

*/


int main()
{
    auto m = imageProcessing::read_image("l.pgm");
    imageProcessing::write_image("m.pgm", m);
    return 0;
}
