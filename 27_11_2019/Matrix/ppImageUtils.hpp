#ifndef __PP_IMAGE_UTILS__
#define __PP_IMAGE_UTILS__
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <sstream>
#include <vector>
#include "Matrix.hpp"

namespace implementation
{
static char filemod[100];
static int bits;
Matrix read_pgm_image(const char* filnam);
void write_pgm_image(const char* filnam, const Matrix &img);
} // namespace implementation

namespace imageProcessing
{
Matrix read_image(std::string);
void write_image(std::string filename, const Matrix &);
} // namespace imageProcessing
#endif