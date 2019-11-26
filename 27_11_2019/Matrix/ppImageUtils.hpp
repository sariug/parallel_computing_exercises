#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <sstream>
#include <vector>
#include "Matrix.hpp"

std::vector<std::vector<int>> read_pgm_image(char filnam[], char filemod[], char comment[], int &R, int &C, int &bits);
void write_pgm_image(char filnam[], char filtype[], const std::vector<std::vector<double>> &img, int vals[]);


namespace imageProcessing
{
Matrix read_image(std::string);
void write_image(std::string filename, const Matrix &);
} // namespace imageProcessing