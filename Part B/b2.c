//Write MPI program to compute dot product of two vectors using block-striped partitioning with uniform data distribution.
#include<stdio.h>
#include "mpi.h"

void main(int argc, char **argv)
{
    int vecsize, rank, size, scatterSize;
    printf("Enter size of vectors:");
    scanf("%d", &vecsize);
    int A[vecsize], B[vecsize], C[vecsize], buffA[vecsize], buffB[vecsize], buffC = 0, result;

    printf("Enter vector A:");
    for(int i =0; i<vecsize; i++)
        scanf("%d", &A[i]);

    printf("Enter vector B:");
    for(int i =0; i<vecsize; i++)
        scanf("%d", &B[i]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(vecsize % size != 0)
    {
        printf("Distribution cannot be uniform");
        exit(0);
    }

    MPI_Bcast(A, vecsize, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, vecsize, MPI_INT, 0, MPI_COMM_WORLD);

    scatterSize = vecsize / size;

    MPI_Scatter(A, vecsize, MPI_INT, buffA, scatterSize, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(B, vecsize, MPI_INT, buffB, scatterSize, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = 0; i < scatterSize; i++)
        buffC += buffA[i] * buffB[i];

    MPI_Reduce(buffC, result, 1, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0)
        printf("Dot product of the two vectors: %d", result);

    MPI_Finalize();
}
