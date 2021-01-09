//Write a program to show how first private clause works. (Factorial program)

#include<stdio.h>
#include<omp.h>
void  main()
{
    int n;
    printf("Factorial of:");
    scanf("%d", &n);
    int fact = 1;
    #pragma omp parallel for firstprivate(n, fact) num_threads(4)       //firstprivate clause makes sure that each thread gets a copy of the variable intialized with a value it had before the clause
    {
        for(; n > 0; n--)
           fact *= n;
    }

    printf("Factorial : %d", fact);
}
