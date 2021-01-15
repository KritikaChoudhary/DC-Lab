//C program which creates new communicators involving a subset of initial set of MPI processes in the default communicator MPILD
#include<stdio.h>
#include "mpi.h"

void main(int argc, char **argv)
{
    MPI_Group groupId, evenGroupId, oddGroupId;
    MPI_Comm EVEN_Comm, ODD_Comm;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm_group(MPI_COMM_WORLD, &groupId);

    int evenPSize = size / 2;
    int oddPSize = (size + 1) / 2;
    int evenRanks[evenPSize], oddRanks[oddPSize];

    int j = 0;
    for(int i = 0; i < evenPSize; i += 2)
    {
        evenRanks[j++] = i;
    }

    int j = 0;
    for(int i = 1; i < oddPSize; i += 2)
    {
        oddRanks[j++] = i;
    }

    MPI_Group_incl(groupId, evenPSize, evenRanks, &evenGroupId); //creating a group of even ranks
    MPI_Comm_create(MPI_COMM_WORLD, evenGroupId, &EVEN_Comm); //creating a new communicator consisting of only even processes

    MPI_Group_incl(groupId, oddPSize, oddRanks, &oddGroupId); //creating a group of odd ranks
    MPI_Comm_create(MPI_COMM_WORLD, oddGroupId, &ODD_Comm); //creating a new communicator consisting of only odd processes

    int evenId, oddId;

    if(rank % 2 == 0)
    {
        MPI_Comm_rank(EVEN_Comm, &evenId);
    } else {
        MPI_Comm_rank(ODD_Comm, &oddId);
    }

    if(evenId == 0)
        printf("Processes in even communicator : %d", evenPSize);

    if(oddId == 0)
        printf("Processes in odd communicator : %d", oddPSize);
}
