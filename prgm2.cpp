#include<iostream>
#include<omp.h>
#include<malloc.h>

using namespace std;

int main()
{
    int sec, items, *allitems, total = 0, i, j, threads;

    cout << "Enter number of sections: ";
    cin >> sec;
    cout << "Enter the number of items: ";
    cin >> items;

    allitems = (int*)malloc(sec*items * sizeof(int));
    cout << "Enter the items:" << endl;
    for(int i = 0; i < sec; i++) {
        cout << "Section " << i+1 << endl;
        for(j = 0; j < items; j++) {
            cin >> allitems[i*items + j];
        }
    }
    omp_set_num_threads(2);
    #pragma omp parallel for num_threads(4)
    for (i = 0; i < sec; i++)
    {
        for(j = 0; j < items; j++)
        {
            #pragma omp critical
            {
                total += allitems[i*items + j];
            }
        }
        threads = omp_get_num_threads();
    }
    cout << " Total cost " << total;
    cout << " Threads " << threads;
    return 0;
    
}