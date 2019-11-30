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
#include <thread>
#include <cassert>

namespace implementation
{
static char filemod[100];
static int bits;
Matrix read_pgm_image(const char *filnam);
void write_pgm_image(const char *filnam, const Matrix &img);
} // namespace implementation
namespace imageProcessing::masks
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
Matrix read_image(std::string);
void write_image(std::string filename, const Matrix &);
} // namespace imageProcessing

void test();
Matrix row_wise_parallel_masked_image_generator(Matrix &input, double *mask, int number_of_threads);
Matrix column_wise_parallel_masked_image_generator(Matrix &input, double *mask, int number_of_threads);
Matrix cross_wise_parallel_masked_image_generator(Matrix &input, double *mask, int number_of_threads);
void threadwise_masking(Matrix &input, double *mask, int begin, int end, int other_dim, Matrix &result);
void threadwise_masking_cross(Matrix &input, double *mask, int begin, int end, int begin_other, int end_other, Matrix &result);
void check(Matrix &input);
Matrix masked_image_generator(Matrix &input, double *mask);
double CalculateConvolution(Matrix &input, double *mask, int i, int j);
void increase(Matrix &input);

#endif