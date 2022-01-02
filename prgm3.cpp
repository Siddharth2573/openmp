#include<iostream>
#include<omp.h>

#define NUM_THREADS 4

int num_steps = 100000;
double step;

using namespace std;

int main()
{
    int nthreads;

    double pi = 0.0, sum[NUM_THREADS];

    step = 1.0 / (double)num_steps;

    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        int id, nt;
        double x;

        id = omp_get_thread_num();

        nt = omp_get_num_threads();

        if(id == 0) {
            nthreads = nt;
        }
        sum[id] = 0.0;

        for(int i = id; i < num_steps; i+=nt) {
            x = (i + 0.5) * step;
            sum[id] += 4.0 / (1.0 + x * x);
        }
    }

    for(int i = 0; i < nthreads; i++) {
        pi += sum[i] * step;
    }
    cout<<"The value of pi is: "<<pi<<endl;
}