//Write parallel program using OpenMP to sort n element using merge sort.

#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#define n 6

void merge(double a[], int low, int mid, int high)
{
	double temp[high + 1];
	int i,j,k;
	
	for(i = low, j = mid+1, k = low; i <=mid && j <=high; k++)
	{
		if(a[i] < a[j])
			temp[k] = a[i++];
		else
			temp[k] = a[j++]; 
	}
	while(i <=mid)
		temp[k++] = a[i++];
	while(j <=high)
		temp[k++] = a[j++];
	
	for(i = low; i<=high; i++)
		a[i] = temp[i];
}

void mergesort(double a[], int low, int high)
{
	int mid;
	
	if(low < high)
	{
		mid = (low + high) / 2;
		
		#pragma omp parallel sections num_threads(4)
		{
			#pragma omp section
			{
				mergesort(a, low, mid);
			}
			#pragma omp section
			{
				mergesort(a, mid+1, high);
			}
		
		}
		merge(a, low, mid, high);
	}
}

void main()
{
	double a[n]; 
	
	for(int i = 0; i  < n; i++)
	{		
		a[i] = rand() % 10;
	}
	
	double start = omp_get_wtime();
	mergesort(a, 0, n-1);
	double timeElapsed = omp_get_wtime() - start;
		
	for(int j = 0; j<n; j++)
		printf("%f\t",a[j]); 
			
	printf("Time: %f\n",timeElapsed);
		
}
	
 



