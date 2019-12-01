#ifndef __PP_IMAGE_UTILS__
#define __PP_IMAGE_UTILS__
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <sstream>
#include <vector>
#include "MatrixUtils.hpp"
#include <thread>
#include <cassert>

namespace implementation
{
static char filemod[100];
static int bits;
Matrix read_pgm_image(const char *filnam);
void write_pgm_image(const char *filnam, const Matrix &img);
} // namespace implementation
namespace imageProcessing::masks // This namespacing requires c++17 
{
extern double blur[9];
extern double edge_detection[9];
extern double sharpen[9];
} // namespace imageProcessing::masks
namespace imageProcessing
{

enum CalculationMethod
{
    Serial,
    ParallelRowwise,
    ParallelColumnwise,
    ParallelCross
};
Matrix apply_mask_to_image(const Matrix &input, double *mask, imageProcessing::CalculationMethod method, int number_of_threads=1);
void threadwise_masking(const Matrix &input, double *mask, int begin, int end, int other_dim, Matrix &result);
void threadwise_masking_cross(const Matrix &input, double *mask, int begin, int end, int begin_other, int end_other, Matrix &result);
double calculate_convolution(const Matrix &input, double *mask, int i, int j);
Matrix read_image(std::string);
void write_image(std::string filename, const Matrix &);
void test_image_processing_methods();
} // namespace imageProcessing



#endif