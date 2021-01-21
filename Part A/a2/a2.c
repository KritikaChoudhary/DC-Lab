//Write a program to Multiply a matrix by a vector and get the result of the operation

#include<stdio.h>
#include<omp.h>

int main()
{
    int n, m, i, j;

    printf("Rows:");
    scanf("%d", &m);
    printf("Columns:");
    scanf("%d", &n);

    int matrix[m][n], vector[n], result[n];

    printf("Enter matrix\n");

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\nEnter vector: \n");

    for(j = 0; j < n; j++)
    {
        scanf("%d", &vector[j]);
    }

    #pragma omp parallel shared(matrix, vector, result) private(i, j)   //matrix and vector are only read by threads, hence,
                                                                        //shared. result is shared among all the threads but
                                                                        //declaring i private ensures that each thread will work
                                                                        //on a separate position of result.
    {
        #pragma omp for scheduled(static)   //omp for distributes each for loop iteration among different threads.
                                        //scheduled(static) : divides loops among threads as - no. of iteration/no. of threads
        {
            for(i = 0; i < m; i++)
            {
                result[i] = 0;
                for(j = 0; j < n; j++)
                {
                    result[i] += matrix[i][j] * vector[j];
                }
            }
        }
    }

    printf("\nResult\n");

    for(j = 0; j < n; j++)
    {
        printf("%d\n", result[j]);
    }
}
