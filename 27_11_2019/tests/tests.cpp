#define CATCH_CONFIG_MAIN
#include "../../external/catch.hpp"
#include <../SimpleImageProcessing/ppImageUtils.hpp>
/*
    Test main file

	Author: Uğurcan Sari
	Date : 2.12.2019

*/


TEST_CASE( "1: All test cases reside in other .cpp files (empty)", "[multi-file:1]" ) {
	imageProcessing::test_image_processing_methods();
}