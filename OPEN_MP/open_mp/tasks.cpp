#include<iostream>
#include<stdio.h>
#include<omp.h>
#include<iomanip>
#include<vector>
#include<random>
#include<chrono>
#include<cstdlib>
using namespace std;

int main()
{

	//TASK - 1
	long long int i,N;
	N =1000000000;
	double h, x, sum, PI;
	h = 1.0 / N;
	//0.000115437445282307
	sum = 0;

	// (max > v[i]) ? max = max : v[i];

#pragma omp parallel default(shared) private(i,x)
	{
		//printf("%d", omp_get_num_threads());
#pragma omp for reduction (+:sum) nowait
		
			for (i = 0; i < N; i++)
			{
				//printf("%d\n",omp_get_thread_num());

				x = h * (i - 0.5);
				sum = sum + (4.0 / (1.0 + x * x));

			}
		
	}
	PI = h * sum;
	

	cout << "Pi= " <<setprecision(15)<<PI<<"\n";
	cout << "Pi difference = " << setprecision(15) << PI- 3.14159265358979323846 << "\n";


	// TASK - 2
	for (int threads = 2; threads < 13; threads= threads+2)
	{
		

		std::random_device rd;
		std::mt19937_64 gen(rd());
		std::uniform_real_distribution<> dis(1.0, 100.0);
		std::vector<double>x, y;
		double minx = 400, maxx = -2, miny = 400, maxy = -2;
		int n = 10000000, j;
		x.resize(n);
		y.resize(n);
		for (int i = 0; i < n; i++)
		{
			x[i] = dis(gen);
			y[i] = dis(gen);
			//std::cout << x[i] << " " << y[i] << "\n";

		}
		auto start = std::chrono::high_resolution_clock::now();

		for (int j = 0; j < n; j++)
		{
			maxx = (maxx > x[j]) ? maxx : x[j];
			minx = (minx < x[j]) ? minx : x[j];
			maxy = (maxy > y[j]) ? maxy : y[j];
			miny = (miny < y[j]) ? miny : y[j];
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> duration = end - start;
		std::cout << "Sum Test serial took " << duration.count() << " ms\n";
		std::cout << maxx << " " << minx << "\n";
		std::cout << maxy << " " << miny << "\n";



		minx = 400, maxx = -2, miny = 400, maxy = -2;
		omp_set_num_threads(4);
		//Parallelized code
		omp_set_num_threads(threads);
		double glob_x = -2, glob_y = -2, glob_min_x = 400, glob_min_y = 400;
		start = std::chrono::high_resolution_clock::now();
#pragma omp parallel firstprivate(maxx, maxy, minx, miny, j)
		{

#pragma omp for
			for (j = 0; j < n; j++)
			{

				maxx = (maxx > x[j]) ? maxx : x[j];
				minx = (minx < x[j]) ? minx : x[j];
				maxy = (maxy > y[j]) ? maxy : y[j];
				miny = (miny < y[j]) ? miny : y[j];

			}
#pragma omp critical
			{

				glob_x = (maxx > glob_x) ? maxx : glob_x;
				glob_min_x = (minx < glob_min_x) ? minx : glob_min_x;
				glob_y = (maxy > glob_y) ? maxy : glob_y;
				glob_min_y = (miny < glob_min_y) ? miny : glob_min_y;


			}

		}
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		std::cout << "Sum Test parallel took " << duration.count() << " ms for threads= "<<threads<<"\n";
		printf("This is the parallelized result \n");

		std::cout << glob_x << " " << glob_min_x << "\n";
		std::cout << glob_y << " " << glob_min_y << "\n";

	}

	system("Pause");

	return 0;
}

