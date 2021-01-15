//Write a program for communication among two processes.
#include<stdio.h>
#include<mpi.h>
#include<string.h>

int main(int argc, char **argv)
{
    int rank, size;
    char* message;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
    {
        message = "Hello from the master process";
        MPI_Send(&message, 4, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&message, 4, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        printf("Message from the master received by the slave : ", message);
    }

    return 0;
}
