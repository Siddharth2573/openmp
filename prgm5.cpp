#include <iostream>
#include <omp.h>
#include<malloc.h>

using namespace std;
/* Main Program */
int main()
{
    int i, N;
    float *array, *check;

    /* Size Of An Array */
    cout << "Enter the size \n";
    cin >> N;

    if (N <= 0) {
        cout << "Array Size Should Be Of Postive Sign \n";
        exit(1);
    }

    /* Dynamic Memory Allocation */
    array = (float *) malloc(sizeof(float) * N);
    check = (float *) malloc(sizeof(float) * N);

    /* Initialization Of Array Elements */
    for (i = 0; i < N; i++) {
        array[i] = i * 1;
        check[i] = i * 1;
    }

    /* The Input Array Is */
    cout << "The Input Array Is\n";
    for (i = 0; i < N; i++)
        cout << "\t" << array[i];
    cout << endl;

    /* OpenMP Parallel For Directive And Critical Section */
    #pragma omp parallel for
        for (i = 1; i < N; i++) {
            #pragma omp critical
            array[i] = (array[i - 1] + array[i]) / 2;
        }
        /* Serial Calculation */
        for (i = 1; i < N; i++)
            check[i] = (check[i - 1] + check[i]) / 2;
        /* Output Checking */
        for (i = 0; i < N; i++) {
            if (check[i] == array[i])
                continue;
            else {
                cout << "There is a difference in the parallel and serial calculation \n";
                exit(1);
            }
        }
        /* The Final Output */
        cout << "\nThe Array Calculation Is Same Using Serial And OpenMP Directives\n";
        cout << "The Output Array Is \n";
        for (i = 0; i < N; i++)
            cout << "\n" << array[i] << "\t"; 
        cout << endl;
        
    /* Freeing The Memory */
    free(array);
    free(check);

    return 0;
}
