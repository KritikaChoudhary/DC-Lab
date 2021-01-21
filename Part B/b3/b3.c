//Write MPI program that computes the value of PI using Monto-Carlo Algorithm.

//when compiling don't forget to add -lm : mpicc b3.c -lm

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<mpi.h>
#include<math.h>

void main(int argc, char **argv)
{
	int rank, size, processIterations, count = 0, result;
	long int iterations = 10000000;
	long int seed = time(NULL);
	double x, y, PI, timeelapsed;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	processIterations = iterations / size;
	
	srand(seed + rank);
	
 	double start = MPI_Wtime();
	
	for(int i = 0; i < processIterations; i++)
	{
		x = (double)rand() / RAND_MAX;  //don't forget to typecast rand
		y = (double)rand() / RAND_MAX;
		
		if(sqrt(x*x + y*y <= 1))
			count++;
	}
	
	double total = MPI_Wtime() - start;
	
	MPI_Reduce(&count, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&total, &timeelapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD); 
	
	if(rank == 0)
	{
		PI = 4 * result / (double)iterations;
		printf("Value of PI : %f", PI); 
		printf("\nAtual value of PI : %f\n",  M_PI);
		printf("Error in value: %f\n", M_PI - PI);
		printf("Total time taken:%f\n", timeelapsed);
	}

	MPI_Finalize();
}

