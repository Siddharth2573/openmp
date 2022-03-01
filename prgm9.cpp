#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[])
{
    int sum = 0;
    int MyRank, Numprocs, Root = 0;

    MPI_Status status;

    /*....MPI Initialisation....*/
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&Numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);

    /*....The REDUCE function of MPI....*/
    MPI_Reduce(&MyRank, &sum, 1, MPI_INT, MPI_SUM, Root, MPI_COMM_WORLD);

    if(MyRank == Root) 
        printf("SUM = %d\n", sum);

    MPI_Finalize();

    return 0;
}