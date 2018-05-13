#include <iostream>
#include <iomanip>
#include <cfloat>
#include <immintrin.h>
#include <assert.h>

using namespace std;

typedef __m256d (*integrable)(__m256d);

static __m256d parabola(__m256d x)
{ return _mm256_mul_pd(x, x); }


int main(int argc, char *argv[])
{
    const unsigned long long steps = 1000000;
    const unsigned int bytes_per_register = 32;
    double a = 0;
    double b = 1;
    double h = (b - a) / (steps * 1.0);
    __m256d sum = _mm256_setzero_pd();

    integrable f = parabola;
    clock_t begin = clock();
    const unsigned int vals_per_register = bytes_per_register / sizeof(double);
    assert(vals_per_register == 4);
    const unsigned int total_blocks = steps / vals_per_register;
    for (unsigned int i = 0; i <= total_blocks; i++)
    {
        __m256d x;
        for (int j = 0; j < vals_per_register; j++) x[j] = a + (i * vals_per_register + j) * h;
        sum = _mm256_add_pd(sum, f(x));
    }
    double total_sum = 0;
    for (int i = 0; i < vals_per_register; i++) total_sum += sum[i];
    total_sum *= h;
    cout << fixed << setprecision(DBL_DIG) << total_sum << endl;
    clock_t end = clock();
    cout << fixed << setprecision(DBL_DIG) << double(end - begin) / (1.0 * CLOCKS_PER_SEC) << " seconds." << endl;
    return 0;
}

