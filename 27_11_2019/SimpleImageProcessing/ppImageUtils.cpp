#include "ppImageUtils.hpp"
using namespace std;

namespace imageProcessing
{
Matrix apply_mask_to_image(Matrix &input, double *mask, imageProcessing::CalculationMethod method, int number_of_threads)
{
	Matrix result(input.numberOfRows() - 2, input.numberOfCols() - 2, 0);
	if (method == imageProcessing::CalculationMethod::Serial)
	{
		for (int i = 1; i < input.numberOfRows() - 1; ++i)
			for (int j = 1; j < input.numberOfCols() - 1; j++)
			{
				result(i - 1, j - 1) = calculate_convolution(input, mask, i, j);
			}
		return result;
	}
	double rows = input.numberOfRows() - 2;
	double cols = input.numberOfCols() - 2;
	std::vector<std::thread> threads;

	switch (method)
	{
	case imageProcessing::CalculationMethod::ParallelColumnwise:
	{
		int chunk = cols / number_of_threads;
		for (int i = 0; i < number_of_threads - 1; ++i)
		{
			threads.emplace_back(threadwise_masking, std::ref(input), std::ref(mask), chunk * i, chunk * (i + 1), rows, std::ref(result));
		}
		threadwise_masking(input, mask, (number_of_threads - 1) * chunk, cols, rows, result);
		break;
	}
	case imageProcessing::CalculationMethod::ParallelRowwise:
	{
		if (number_of_threads > input.numberOfRows() - 3)
		{
			throw std::runtime_error("!!!The number of threads shouldn't exceed the number of rows");
		}
		int chunk = rows / number_of_threads;
		for (int i = 0; i < number_of_threads - 1; ++i)
		{
			threads.emplace_back(threadwise_masking, std::ref(input), std::ref(mask), chunk * i, chunk * (i + 1), cols, std::ref(result));
		}
		threadwise_masking(input, mask, (number_of_threads - 1) * chunk, rows, cols, result);

		break;
	}
	case imageProcessing::CalculationMethod::ParallelCross:
	{
		if (number_of_threads > input.numberOfRows() + input.numberOfCols() - 6)
		{
			throw std::runtime_error("!!!The number of threads shouldn't exceed the number of rows or columns");
		}
		double ratio, number_of_threadsR, number_of_threadsC;
		//Dividing threads among rows and columns
		ratio = rows / (rows + cols);
		number_of_threadsR = number_of_threads * ratio;
		number_of_threadsC = number_of_threads * (1 - ratio);
		int chunk_row = rows / number_of_threadsR;
		int chunk_col = cols / number_of_threadsC;
		for (int i = 0; i < number_of_threadsR - 1; i++)
		{
			for (int j = 0; j < number_of_threadsC - 1; j++)
			{
				// At each iteration, we create a new thread who gets a function to compute and store the thread in threads vector.
				threads.emplace_back(threadwise_masking_cross, std::ref(input), std::ref(mask), chunk_row * i, chunk_row * (i + 1), chunk_col * j, chunk_col * (j + 1), std::ref(result));
			}
			threadwise_masking_cross(input, mask, chunk_row * i, chunk_row * (i + 1), (number_of_threadsC - 1) * chunk_col, cols, result);
		}
		threadwise_masking_cross(input, mask, number_of_threadsR - 1, rows, 0, cols, result);
		break;
	}
	}
	for (auto &thread : threads)
		thread.join();

	// After joining threads we can safely delete the threads, the answer we want is stored inside sums.
	threads.clear();

	return result;
}

void threadwise_masking(Matrix &input, double *mask, int begin, int end, int other_dim, Matrix &result)
{

	for (int i = begin; i < end; i++)
		for (int j = 0; j < other_dim; j++)
			result(i, j) = calculate_convolution(input, mask, i + 1, j + 1);
}

void threadwise_masking_cross(Matrix &input, double *mask, int begin, int end, int begin_other, int end_other, Matrix &result)
{

	for (int i = begin; i < end; i++)
		for (int j = begin_other; j < end_other; j++)
			result(i, j) = calculate_convolution(input, mask, i + 1, j + 1);
}
double calculate_convolution(Matrix &input, double *mask, int i, int j)
{
	double smoothed = 0.0;

	for (int m = -1; m < 2; ++m)
		for (int n = -1; n < 2; ++n)
		{
			smoothed += input(i - m, j - n) * mask[(m + 1) * 3 + (n + 1)];
		}

	smoothed = std::max(smoothed, 0.0);
	smoothed = std::min(smoothed, 255.0);

	return smoothed;
}
void test_image_processing_methods()
{
	Matrix dummy(2, 3, 1);
	matrixUtilities::pad(dummy);
	for (int i = 1; i < 3; ++i)
		for (int j = 1; j < 4; ++j)
		{
			assert(dummy(i, j) == 1);
		}
	for (int i = 0; i < dummy.numberOfCols(); ++i)
	{
		assert(dummy(0, i) == 0.0);
		assert(dummy(3, i) == 0.0);
	}
	for (int i = 0; i < dummy.numberOfRows(); ++i)
	{
		assert(dummy(i, 0) == 0.0);
		assert(dummy(i, 4) == 0.0);
	}
	std::cout << "Padding test : passed.\n";

	Matrix inp({{0, 0, 8}, {4, -2, 6}, {2, 3, 1}});
	double test_mask[9] = {1, 0, 1, -1, 1, 1, 1, 1, 1};
	double a = imageProcessing::calculate_convolution(inp, test_mask, 1, 1);
	assert(a == 7.0);
	std::cout << "Convolution test : passed.\n";

	double test_mask2[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	int test_number_of_threads = 2;
	Matrix benchmark_result({{2, 16, 12}, {7, 22, 16}, {7, 14, 8}});
	matrixUtilities::pad(inp);
	Matrix result = imageProcessing::apply_mask_to_image(inp, test_mask2, imageProcessing::CalculationMethod::Serial);
	Matrix result_1 = imageProcessing::apply_mask_to_image(inp, test_mask2, imageProcessing::CalculationMethod::ParallelRowwise, test_number_of_threads);
	Matrix result_2 = imageProcessing::apply_mask_to_image(inp, test_mask2, imageProcessing::CalculationMethod::ParallelColumnwise, test_number_of_threads);
	Matrix result_3 = imageProcessing::apply_mask_to_image(inp, test_mask2, imageProcessing::CalculationMethod::ParallelCross, test_number_of_threads);

	assert(result == benchmark_result);
	std::cout << "Serial mask application test : passed." << std::endl;
	assert(result_1 == benchmark_result);
	std::cout << "Parallel row wise mask application test : passed." << std::endl;
	assert(result_2 == benchmark_result);
	std::cout << "Parallel column wise mask application test : passed." << std::endl;
	assert(result_3 == benchmark_result);
	std::cout << "Parallel cross mask application test : passed." << std::endl;
	std::cout << "\nAll tests are passed.\n"
			  << std::endl;
}

Matrix read_image(std::string filename)
{
	return Matrix(implementation::read_pgm_image(filename.c_str()));
}
void write_image(std::string filename, const Matrix &img)
{
	implementation::write_pgm_image(filename.c_str(), img); /*Writing the PGM in Binary (P5) format*/
}
} // namespace imageProcessing
namespace imageProcessing::masks
{
double blur[9] = {1 / 9., 1 / 9., 1 / 9., 1 / 9., 1 / 9., 1 / 9., 1 / 9., 1 / 9., 1 / 9.};
double edge_detection[9] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
double sharpen[9] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
} // namespace imageProcessing::masks

/* Implementations of reader and writer*/
namespace implementation
{

Matrix read_pgm_image(const char *filnam) /*reads PGM images*/
{
	ifstream ifs;
	ifstream iftest;
	string newlin;
	iftest.open(filnam, ios::in);
	if (!iftest.is_open())
	{
		std::cout << filnam << " does not exist.Quitting." << std::endl;
		exit(400);
	}
	int header_size = 3;

	for (int i = 0; i < 4; i++)
	{

		getline(iftest, newlin);

		if (newlin.data()[0] == '#')
		{
			header_size = 4;
			break;
		}
	}

	iftest.close();

	ifs.open(filnam, ios::in);
	int C = 0, R = 0;
	for (int i = 0; i < 4; i++)
	{
		streampos old = ifs.tellg();
		getline(ifs, newlin);

		int N1;
		stringstream t(newlin);
		t >> N1;

		if (strcmp(newlin.data(), "P2") == 0 | strcmp(newlin.data(), "P5") == 0)
		{
			strcpy(filemod, newlin.data());
		}
		else if (newlin.data()[0] == '#')
		{
		}
		else if (t)
		{

			int NN;
			t >> NN;
			if (t)
			{
				C = N1;
				R = NN;
			}
			else
			{
				implementation::bits = N1;
			}
		}
		else
		{
			std::cout << "\n Overread into bits!! Going back to bit line!!! \n";
			ifs.seekg(old);
			break;
		}
	}

	ifs.close();

	ifstream newp;
	newp.open(filnam, ios::in | ios::binary);

	char tt;
	newp >> tt;

	for (int i = 0; i < header_size; i++)
		getline(newp, newlin);
	cout << "The image imported is : " << filnam << std::endl;
	cout << "\tFiletype : " << filemod << std::endl;
	cout << "\t"
		 << "Height : " << R << std::endl;
	cout << "\t"
		 << "Width : " << C << std::endl;
	cout << "\t"
		 << "Maximum Value : " << bits << std::endl;

	Matrix m_img(R, C);

	long cnt = 0;

	for (auto k = 0; k < R; k++)
	{
		for (auto l = 0; l < C; l++)
		{

			if (newp.eof() == 1)
				break;

			int val = 0;
			int p = 7;
			char c11;
			newp.get(c11);

			while (p >= 0)
			{

				val += (((c11 >> p) & 1)) * pow(2, p);
				p--;
			}

			m_img(k, l) = val;

			cnt++;
		}
	}

	newp.close();

	return m_img;
}
void write_pgm_image(const char *filnam, const Matrix &img) /*writes PGM images*/
{
	int R, C;
	C = img.numberOfCols();
	R = img.numberOfRows();

	ofstream off;

	off.open(filnam, ios::out);
	off << implementation::filemod << "\n"
		<< "# Filename :: CV 2017 " << filnam << "\n"
		<< C << " " << R << "\n"
		<< implementation::bits << "\n";
	cout << "The image exported is : " << filnam << std::endl;
	cout << "\tFiletype : " << filemod << std::endl;
	cout << "\t"
		 << "Height : " << R << std::endl;
	cout << "\t"
		 << "Width : " << C << std::endl;
	cout << "\t"
		 << "Maximum Value : " << bits << std::endl;
	off.close();

	ofstream newof;

	newof.open(filnam, ios::out | ios::binary | ios::app);
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			newof.put(static_cast<int>(img(i, j)));
	newof.close();
}
} // namespace implementation
