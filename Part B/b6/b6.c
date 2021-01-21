//C program which searches integers between A and B for a value J such that F(J) = C, using the MPI parallel programming environment

#include<stdio.h>
#include<mpi.h>
#include<math.h>

int F(int val)
{
	return val * val;
}

int search(int a, int b, int c, int rank, int size)
{

	for(int i = a + rank; i <= b && i > 0; i += size)
	{
		if(c == F(i))
		{
			return i;
		}
	}
	return -1;
}

void main(int argc, char **argv)
{

	int rank, size, A = 1, B = 100000, C = 53;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	double start = MPI_Wtime();
	int solution = search(A, B, C, rank, size);
	double elapsed = MPI_Wtime() - start;
	
	if(solution != -1)
	{
		printf("F(%d) = %d X %d = %d\n", solution, solution, solution, C);
		printf("Time elapsed : %f\n", elapsed);
	}
	
	MPI_Finalize();
} 
		
