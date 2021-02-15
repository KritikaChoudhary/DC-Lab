//C program which creates new communicators involving a subset of initial set of MPI processes in the default communicator MPILD

/*a communicator is created from a group. First the group is created with the 
desired processes to be included within the group and then the group is used to 
create a communicator. So keep in mind that you must have a group defined before 
you can create a new communicator.*/

/*
-Creating a group
Using MPI_Comm_group create a handle to the global group MPI_COMM_WORLD
Create a new group as a subset of the global group, MPI_COMM_WORLD in this example, 
using MPI_Group_incl
-Creating a communicator
Using the newly created group from above create a communicator from the group 
using MPI_Comm_create
-Destroying a group/communicator
When done using the created group and/or communicator you can free it by 
using MPI_Comm_free and MPI_Group_free
*/

#include<stdio.h>
#include "mpi.h"
#include<stdlib.h>

void main(int argc, char **argv)
{
    MPI_Group groupId, evenGroupId, oddGroupId;   //MPI_Group is a set of processes
    MPI_Comm EVEN_Comm, ODD_Comm;
    
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);   //MPI_COMM_WORLD : communicator, holds a group of processes 
                                            //that can communicate with each other
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    

    MPI_Comm_group(MPI_COMM_WORLD, &groupId);   //gets the process group from the default communicator 

    int oddPSize = size / 2;
    int evenPSize = (size + 1) / 2;
    int evenRanks[evenPSize], oddRanks[oddPSize];

    int j = 0;
    for(int i = 0; i < size; i += 2)
    {
        evenRanks[j++] = i;
        
    }

    j = 0;
    for(int i = 1; i < size; i += 2)
    {
        oddRanks[j++] = i;
        
    }

    MPI_Group_incl(groupId, evenPSize, evenRanks, &evenGroupId); //allows you to pick specific ranks in a group and construct 
                                                                 //a new group containing only those ranks
                                                                //creating a group of even ranks
    MPI_Comm_create(MPI_COMM_WORLD, evenGroupId, &EVEN_Comm); //creating a new communicator consisting of only even processes

    MPI_Group_incl(groupId, oddPSize, oddRanks, &oddGroupId); //creating a group of odd ranks
    MPI_Comm_create(MPI_COMM_WORLD, oddGroupId, &ODD_Comm); //creating a new communicator consisting of only odd processes
        
    int oddrank,evenrank;
    int evensum, oddsum;
    int isodd, iseven;
    
    if(rank %2 != 0)
    {
    	MPI_Comm_rank(ODD_Comm, &oddrank);
    	iseven = -1;
    }
   
    if(rank % 2 == 0)
    {
    	MPI_Comm_rank(EVEN_Comm, &evenrank);
    	isodd = -1;
    }
    
    if(isodd != -1)
    	MPI_Reduce(&rank, &oddsum, 1, MPI_INT, MPI_SUM, 0, ODD_Comm);
    if(iseven != -1)
    	MPI_Reduce(&rank, &evensum, 1, MPI_INT, MPI_SUM, 0, EVEN_Comm);
    	
    if(oddrank == 0)
    {
    	printf("\nNo. of processes in odd communicator:%d\n", oddPSize);
    	printf("Sum of odd ranks:%d\n", oddsum);
    }
    	
    if(evenrank == 0)
    {
    	printf("\nNo. of processes in even communicator:%d\n", evenPSize);
    	printf("Sum of even ranks:%d\n", evensum);
    }
    
    MPI_Finalize();
}


