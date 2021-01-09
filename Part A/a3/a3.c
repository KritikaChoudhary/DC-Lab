#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<math.h>

int* primetable(int no_of_primes)
{
    int n = 0, i = 2, prime, *primeT = (int *)malloc(no_of_primes * sizeof(int));

     while(n < no_of_primes)
    {
        prime = 1;
        for(int j = 2; j <= i/2; j++)
        {
            if(i % j == 0)
            {
                prime = 0;
                break;
            }
        }
        if(prime)
        {
            primeT[n++] = i;
        }
        i++;
    }
    return primeT;
}

double* sinetable(int no_of_sine)
{
    double *sineT = (double *)malloc(no_of_sine * sizeof(double)), val;

    for(int i = 0; i < no_of_sine; i++)
    {
        sineT[i] = 0;
        for(int j = 0; j <= i; j++)
        {
            val = j * M_PI + (no_of_sine - 1);
            sineT[i] += sin(val);
        }
    }

    return sineT;
}

void main()
{
    int no_of_primes, no_of_sines, *primeTable;
    double *sineTable;

    printf("Enter no. of primes and no. of sines:");
    scanf("%d%d", &no_of_primes, &no_of_sines);


    #pragma omp parallel shared(no_of_sines, sineTable, no_of_primes, primeTable)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                primeTable = primetable(no_of_primes);
            }
            #pragma omp section
            {
                sineTable = sinetable(no_of_sines);
            }
        }
    }
    printf("\nPrime table: ");
    for(int  i = 0; i < no_of_primes; i++)
        printf("%d\t", primeTable[i]);

    printf("\nSine table:");
    for(int i = 0; i < no_of_sines; i++)
        printf("%f\t", sineTable[i]);
}
