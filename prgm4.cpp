#include<iostream>
#include<omp.h>

using namespace std;

int main()
{
    int s, a[100], n, i;

    omp_set_num_threads(2);

    cout << "Enter the number of terms: ";

    cin >> n;

    a[0] = 0;
    a[1] = 1;

    #pragma omp parallel
    {
        #pragma omp single
        for(i = 2; i < n; i++) {
            a[i] = a[i-1] + a[i-2];

            cout << "id of " << i+1 << " " << omp_get_thread_num() << endl;
        }
        #pragma omp barrier
        #pragma omp single
        {
            cout << " The elements of Fibonacci series are " << endl;
            for(i = 0; i < n; i++) {
                cout << a[i] << " id of the thread displaying this number is " << omp_get_thread_num() << endl;
            }
        }
    }
    
    return 0;
}