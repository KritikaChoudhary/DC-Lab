//Write MPI program to compute Matrix-Matrix Multiplication using self-scheduling algorithm.

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#define m 3
#define n 2
#define o 3
void main(int argc, char **argv)
{
	int rank, size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int a[n][n], b[n][n], c[n][n];
	int rows, offset;
	
	if(rank == 0)
	{
	
	printf("\n****A****");
	for(int i = 0; i < n; i++)
	{
		printf("\n");
		for(int j = 0; j < n; j++)
		{
			a[i][j] = 5;
			printf("%d\t", a[i][j]);
		}
	}
	
	printf("\n****B****");
	
	for(int i = 0; i < n; i++)
	{
		printf("\n");
		for(int j = 0; j < n; j++)
		{
			b[i][j] = 2;
			printf("%d\t", b[i][j]);
		}
	}
	
	
	rows = n/(size - 1);  //no. of rows of A to be sent
	offset = 0;	//starting index of the row being sent
	
	
	//sending the required values
	for(int i = 1; i<=size-1; i++)
	{
		MPI_Send(&rows, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
		MPI_Send(&offset, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
		MPI_Send(&a[offset][0], rows*n, MPI_INT, i, 1, MPI_COMM_WORLD);
		MPI_Send(&b, n*n, MPI_INT, i, 1, MPI_COMM_WORLD);
		
		offset = offset + rows;
	}
	
	
	//master receiving result from all slave processes
	for(int i = 1; i<=(size - 1); i++)
	{
		MPI_Recv(&offset, 1, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&rows, 1, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&c[offset][0], rows*n, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	
	
	//Print final result
	printf("\n****C****");
	for(int i = 0; i<n; i++)
	{
		printf("\n");
		for(int j = 0; j<n; j++)
		{
			printf("%d\t", c[i][j]); 
		}
	}
	
	}
	
	else
	{
	
		//Receiving values sent by the master
		MPI_Recv(&rows, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&offset, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&a, rows*n, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&b, n*n, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			
				
		for(int i = 0; i<rows; i++)
		{
			for(int j = 0; j<n; j++)
			{
				c[i][j] = 0;
				
				for(int k = 0; k<n; k++)
				{
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		
		//sending result back to master
		MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD); //offset of result matrix
		MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);  //no. of rows of result matrix to be sent
		MPI_Send(&c, rows*n, MPI_INT, 0, 2, MPI_COMM_WORLD); //the result matrix
	}
	
	MPI_Finalize();
	printf("\n");
}
