#include <iostream>
#include <omp.h>

int num_steps = 100000;
double step;
#define NUM_THREADS 2

using namespace std;
int main()
{
    int i, nthreads;
    double pi = 0.0, sum[NUM_THREADS];
    step = 1.0 / (double)num_steps;

    #pragma omp parallel
    {
        int i, id, nt;
        double x;

        id = omp_get_thread_num();
        nt = omp_get_num_threads();

        if(id == 0) nthreads = nt;
        sum[id] = 0.0;
        for(i = id; i < num_steps; i+=nt)
        {
            x = (i + 0.5) * step;
            sum[id] += 4.0 / (1.0 + x * x);
        }
    }
    for(int i = 0; i < nthreads; i++) {
        pi += sum[i] * step;
    }
    cout << "Pi = " << pi << endl;

    return 0;
}