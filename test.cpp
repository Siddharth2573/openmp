#include<iostream>
#include<omp.h>
#include<stdlib.h>

using namespace std;

#define MAXIMUM 65536

int main()
{
    int *array, N, ParallelMax, SerialMax;

    cout << "Enter number of elements: ";
    cin >> N;

    if (N <= 0)
    {
        cout << "The array elements cannot be stored." << endl;
        exit(1);
    }

    array = (int*)malloc(sizeof(int) * N);

    srand(MAXIMUM);

    for(int i = 0; i < N; i++)
        array[i] = rand();
    
    if (N == 1)
    {
        cout << "The largest element of the array is = " << array[0] << endl;
        exit(1);
    }

    ParallelMax = 0;

    #pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        if (array[i] > ParallelMax)
        {
            #pragma omp critical
            if (array[i] > ParallelMax)
            {
                ParallelMax = array[i];
            }
            
        }
        
    }

    SerialMax = 0;

    for (int i = 0; i < N; i++)
    {
        if (array[i] > SerialMax)
        {
            SerialMax = array[i];
        }
    }

    cout << "The input array elements are" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << array[i] << "\t";
    }
    cout << endl;

    if (ParallelMax == SerialMax)
        cout << "The Max value is same from Serial and Parallel execution." << endl;
    else
    {
        cout << "The Max value id not the same from Serial and Parallel execution." << endl;
        exit(1);
    }
    
    cout << "The Largest number is = " << ParallelMax << endl;
    
    free(array);

    return 0;
}