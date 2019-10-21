#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <limits>
#include "triad_naive.h"

int main()
{
	constexpr int N = 1e5;
	constexpr int iter = 100;
	constexpr int Ntimes = 100;

	std::vector<double> a(N, 1.);
	std::vector<double> b(N, 2.);
	std::vector<double> c(N, 3.);
	std::vector<double> d(N, 4.);

	double times[Ntimes];
	double	avgtime = 0.0, maxtime = 0.0, mintime = std::numeric_limits<double>::max();

	for (int k = 0; k < Ntimes; k++) {
		/* times[k]  = triad(a, b, c, d, N, iter); */
		/* times[k]  = triad_intrinsics(a, b, c, d, N, iter); */
		times[k] = triad_naive(a.data(), b.data(), c.data(), d.data(), a.size(), iter);
	}
	for (int k=1; k<Ntimes; k++) {
        avgtime = avgtime + times[k];
        mintime = std::min(mintime, times[k]);
      maxtime = std::max(maxtime, times[k]);
    }
	size_t bytesPerWord = sizeof(double);
    printf("Time: %f sec\n", mintime);
    printf("Working set: %.2f kB\n", 4.0 * N * bytesPerWord / 1000.0);
    printf(" %.2f MB/s\n",1.0E-06 * (double) iter * (double) N*32.0/(mintime*1e-3));
    printf(" %.2f MFLops/s\n",1.0E-06 * (double) iter * (double) N*2.0/(mintime * 1e-3));
	return 0;
}