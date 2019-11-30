#include "ppImageUtils.hpp"
using namespace std;



Matrix EdgeDetection()
{
	Matrix ed(3, 3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			ed(i, j) = -1;

	ed(1, 1) = 8;

	return ed;
}

Matrix Sharpen()
{
	Matrix sh(3, 3, -1);
	sh(0, 0) = 0;
	sh(3 - 1, 1 - 1) = 0;
	sh(1 - 1, 3 - 1) = 0;
	sh(3 - 1, 3 - 1) = 0;
	sh(2 - 1, 2 - 1) = 5;



	return sh;
}

Matrix Blur()
{
	Matrix bl(3, 3, 1.0 / 9.0);

	return bl;
}

void check(Matrix &input)
{
	if (input.numberOfCols() < 3 || input.numberOfRows() < 3)
		throw std::runtime_error("Minimum rows or columns should be 3, check input matrix");
}

Matrix masked_image_generator(Matrix & input, Matrix & convolution)
{
	Matrix res(input.numberOfRows() - 2, input.numberOfCols() - 2, 0);


	for (int i = 1; i < input.numberOfRows() - 1; ++i)
		for (int j = 1; j < input.numberOfCols() - 1; j++)
		{
			res(i - 1, j - 1) = CalculateConvolution(input, convolution, i, j);
		}



	return res;

}

double CalculateConvolution(Matrix & input, Matrix & convolution, int i, int j)
{
	double smoothed = 0.0;

	for (int m = -1; m < 2; ++m)
		for (int n = -1; n < 2; ++n)
		{
			smoothed += input(i - m, j - n)*convolution(m + 1, n + 1);

		}

	smoothed = std::max(smoothed, 0.0);
	smoothed = std::min(smoothed, 255.0);

	return smoothed;
}

void increase(Matrix & input)
{
	Matrix dummy(input.numberOfRows() + 2, input.numberOfCols() + 2, 0.0);
	for (int i = 0; i < input.numberOfRows(); ++i)
		for (int j = 0; j < input.numberOfCols(); ++j)
			dummy(i + 1, j + 1) = input(i, j);

	input = dummy;

}

namespace imageProcessing
{
Matrix read_image(std::string filename)
{
    return Matrix( implementation::read_pgm_image(filename.c_str()));
}
void write_image(std::string filename, const Matrix & img)
{
    implementation::write_pgm_image(filename.c_str(),img);           /*Writing the PGM in Binary (P5) format*/
}
}


/* Implementations of reader and writer*/
namespace implementation
{
    
    Matrix read_pgm_image(const char* filnam) /*reads PGM images*/
    {
        ifstream ifs;
        ifstream iftest;
        string newlin;
        iftest.open(filnam, ios::in);
        if(!iftest.is_open())
        {
            std::cout<<filnam<<" does not exist.Quitting."<<std::endl;
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
        int C=0, R=0;
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
        cout<<"The image imported is : "<<filnam<<std::endl;
        cout << "\tFiletype : "<<filemod<<std::endl;
        cout << "\t"<< "Height : "<<R<<std::endl;
        cout << "\t"<< "Width : "<<C<<std::endl;
        cout << "\t"<< "Maximum Value : "<<bits<<std::endl;

        Matrix m_img(R,C);

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

                m_img(k,l) = val;

                cnt++;
            }
        }

        newp.close();

        return m_img;
    }
    void write_pgm_image(const char* filnam, const Matrix &img) /*writes PGM images*/
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
        cout<<"The image exported is : "<<filnam<<std::endl;
        cout << "\tFiletype : "<<filemod<<std::endl;
        cout << "\t"<< "Height : "<<R<<std::endl;
        cout << "\t"<< "Width : "<<C<<std::endl;
        cout << "\t"<< "Maximum Value : "<<bits<<std::endl;
        off.close();

        ofstream newof;

        newof.open(filnam,ios::out | ios::binary | ios::app);
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)      
                newof.put(static_cast<int>(img(i,j)));
        newof.close();
    }
} // namespace implementation



void test()
{
	Matrix dummy(2, 3, 1);
	increase(dummy);
	for (int i = 1; i < 3; ++i)
		for (int j = 1; j < 4; ++j)
		{
			assert(dummy(i, j) == 1);
		}

	for (int m = 0; m < 5; ++m)
	{
		assert(dummy(0, m) == 0.0);
	}
	for (int i = 0; i < 5; ++i)
	{
		assert(dummy(3, i) == 0.0);
	}
	for (int i = 0; i < 4; ++i)
	{
		assert(dummy(i, 0) == 0.0);
	}
	for (int i = 0; i < 4; ++i)
	{
		assert(dummy(i, 4) == 0.0);
	}

	Matrix ones(3, 3, 1);
	Matrix inp(3, 3, 0);
	inp(0, 2) = 8;
	inp(1, 0) = 4;
	inp(2, 0) = 2;
	inp(1, 1) = -2;
	inp(2, 1) = 3;
	inp(1, 2) = 6;
	inp(2, 2) = 1;
	ones(0, 1) = 0;
	ones(1, 0) = -1;

	double a = CalculateConvolution(inp, ones, 1, 1);
	assert(a == 7.0);


	Matrix on(3, 3, 1);

	increase(inp);
	Matrix result = masked_image_generator(inp, on);
	assert(result(0, 0) == 2);
	assert(result(0, 1) == 16);
	assert(result(0, 2) == 12);
	assert(result(1, 0) == 7);
	assert(result(1, 1) == 22);
	assert(result(1, 2) == 16);
	assert(result(2, 0) == 7);
	assert(result(2, 1) == 14);
	assert(result(2, 2) == 8);

	Matrix result_1 = row_wise_parallel_masked_image_generator(inp, on, 2);
	//Matrix result_1 = column_wise_parallel_masked_image_generator(inp, on, 2);
	//Matrix result_1 = cross_wise_parallel_masked_image_generator(inp, on, 2);
	assert(result_1(0, 0) == 2);
	assert(result_1(0, 1) == 16);
	assert(result_1(0, 2) == 12);
	assert(result_1(1, 0) == 7);
	assert(result_1(1, 1) == 22);
	assert(result_1(1, 2) == 16);
	assert(result_1(2, 0) == 7);
	assert(result_1(2, 1) == 14);
	assert(result_1(2, 2) == 8);

}



Matrix row_wise_parallel_masked_image_generator(Matrix & input, Matrix & convolution, int number_of_threads)
{

	if (number_of_threads > input.numberOfRows() - 3)
	{
		throw std::runtime_error("!!!The number of threads shouldn't exceed the number of rows");
	}


	int size_1 = input.numberOfRows() - 2;
	int size_2 = input.numberOfCols() - 2;
	int numberOfThreads = number_of_threads;
	int chunk = size_1 / numberOfThreads;
	std::vector<std::thread> threads;
	Matrix A = input;
	Matrix B = convolution;
	Matrix result(input.numberOfRows() - 2, input.numberOfCols() - 2);
	for (int i = 0; i < numberOfThreads - 1; ++i)
	{
		// At each iteration, we create a new thread who gets a function to compute and store the thread in threads vector.
		threads.emplace_back(threadwise_masking, std::ref(A), std::ref(B), chunk*i, chunk * (i + 1), size_2, std::ref(result));
	}

	// Main thread does the last chunk until the end of the arrays.
	threadwise_masking(A, B, (numberOfThreads - 1)*chunk, size_1, size_2, result);

	for (auto& thread : threads) thread.join();

	// After joining threads we can safely delete the threads, the answer we want is stored inside sums.
	threads.clear();

	return result;

}

Matrix column_wise_parallel_masked_image_generator(Matrix & input, Matrix & convolution, int number_of_threads)
{

	if (number_of_threads > input.numberOfCols() - 3)
	{
		throw std::runtime_error("!!!The number of threads shouldn't exceed the number of columns");
	}


	int size_1 = input.numberOfRows() - 2;
	int size_2 = input.numberOfCols() - 2;
	int numberOfThreads = number_of_threads;
	int chunk = size_2 / numberOfThreads;
	std::vector<std::thread> threads;
	Matrix A = input;
	Matrix B = convolution;
	Matrix result(input.numberOfRows() - 2, input.numberOfCols() - 2);
	for (int i = 0; i < numberOfThreads - 1; ++i)
	{
		// At each iteration, we create a new thread who gets a function to compute and store the thread in threads vector.
		threads.emplace_back(threadwise_masking, std::ref(A), std::ref(B), chunk*i, chunk * (i + 1), size_1, std::ref(result));
		std::cout << result;
	}

	// Main thread does the last chunk until the end of the arrays.
	threadwise_masking(A, B, (numberOfThreads - 1)*chunk, size_2, size_1, result);
	std::cout << result;
	for (auto& thread : threads) thread.join();

	// After joining threads we can safely delete the threads, the answer we want is stored inside sums.
	threads.clear();

	return result;

}

Matrix cross_wise_parallel_masked_image_generator(Matrix & input, Matrix & convolution, int number_of_threads)
{

	if (number_of_threads > input.numberOfRows() + input.numberOfCols() - 6)
	{
		throw std::runtime_error("!!!The number of threads shouldn't exceed the number of rows or columns");
	}
	double ratio, numberOfThreadsR, numberOfThreadsC;
	double rows = input.numberOfRows() - 2;
	double cols = input.numberOfCols() - 2;


	//Dividing threads among rows and columns

	ratio = rows / (rows + cols);
	numberOfThreadsR = number_of_threads * ratio;
	numberOfThreadsC = number_of_threads * (1 - ratio);
	int size_1 = input.numberOfRows() - 2;
	int size_2 = input.numberOfCols() - 2;
	int numberOfThreads = numberOfThreadsR + numberOfThreadsC;
	int chunk_row = size_1 / numberOfThreadsR;
	int chunk_col = size_2 / numberOfThreadsC;
	std::vector<std::thread> threads;
	Matrix A = input;
	Matrix B = convolution;
	Matrix result(input.numberOfRows() - 2, input.numberOfCols() - 2);
	for (int i = 0; i < numberOfThreadsR - 1; i++)
	{
		for (int j = 0; j < numberOfThreadsC - 1; j++)
		{
			// At each iteration, we create a new thread who gets a function to compute and store the thread in threads vector.
			threads.emplace_back(threadwise_masking_cross, std::ref(A), std::ref(B), chunk_row*i, chunk_row * (i + 1), chunk_col*j, chunk_col * (j + 1), std::ref(result));
		}
		threadwise_masking_cross(A, B, chunk_row*i, chunk_row * (i + 1), (numberOfThreadsC - 1)*chunk_col, size_2, result);
	}
	threadwise_masking_cross(A, B, numberOfThreadsR - 1, size_1, 0, size_2, result);

	// Main thread does the last chunk until the end of the arrays.


	for (auto& thread : threads) thread.join();

	// After joining threads we can safely delete the threads, the answer we want is stored inside sums.
	threads.clear();

	return result;

}

void threadwise_masking(Matrix & input, Matrix & convolution, int begin, int end, int other_dim, Matrix & result)
{

	for (int i = begin; i < end; i++)
		for (int j = 0; j < other_dim; j++)
			result(i, j) = CalculateConvolution(input, convolution, i + 1, j + 1);

}

void threadwise_masking_cross(Matrix & input, Matrix & convolution, int begin, int end, int begin_other, int end_other, Matrix & result)
{

	for (int i = begin; i < end; i++)
		for (int j = begin_other; j < end_other; j++)
			result(i, j) = CalculateConvolution(input, convolution, i + 1, j + 1);



}