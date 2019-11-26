#include "MatrixUtils.hpp"
#include "ppImageUtils.hpp"
/*
    A simple Matrix class and Utils to manipulate matrices.

	Author: Uğurcan Sarı, Oguz Oztoprak
	Date : 20.11.2019

*/


int main()
{
auto m = imageProcessing::read_image("l.pgm");
imageProcessing::write_image("m.pgm", m);
return 0;
}
