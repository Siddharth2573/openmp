#include<iostream>
#include<omp.h>
#include<malloc.h>

using namespace std;

int main()
{
    int n, threads;

    cout<<"Enter the dimension: ";
    cin>>n;

    int mat[100][100], vec[100];

    cout<<"Enter the matrix: "<<endl;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin>>mat[i][j];
        }
    }
    cout<<"Enter the vector: "<<endl;
    for(int i = 0; i < n; i++) {
        cin>>vec[i];
    }

    omp_set_num_threads(2);

    #pragma omp parallel for num_threads(4)
    for(int i = 0; i < n; i++) {
        int total = 0;
        for(int j = 0; j < n; j++) {
            #pragma omp critical
            {
                total += mat[j][i] * vec[j];
            }
        }
        cout<<total<<" ";
        threads = omp_get_num_threads();
    }
    cout<<"\nThreads "<<threads;

    return 0;
}