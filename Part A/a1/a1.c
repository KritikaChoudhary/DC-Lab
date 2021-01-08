#include<stdio.h>
#include<omp.h>

void merge(int a[], int low, int mid, int high)
{
    int j = low;
    int k = mid;
    int temp[50];
    int i;
    for(i = low; j < mid && k < high; i++)
    {
        if(a[j] < a[k])
        {
            temp[i] = a[j];
            j++;
        }
        else
        {
            temp[i] = a[k];
            k++;
        }
    }
    if(j < mid)
    {
        for(;j < mid; j++)
        {
            temp[i++] = a[j];
        }
    }
    else
    {
        for(;k < high; k++)
        {
            temp[i++] = a[k];
        }
    }
    for(int i = 0; i < high; i++)
    {
        a[i] = temp[i];
    }
}

void mergesort(int a[], int low, int high)
{
    int mid;
    if(low < high)
    {
        mid = (low + high) / 2;

        #pragma omp parallel sections num_threads(2)        //creates 2 threads and iddentifies the code section that is to be divided among the threads
        {
            #pragma omp section         //distributes work among threads
            {
                mergesort(a, low, mid);
            }
            #pragma omp section
            {
                mergesort(a, mid + 1, high);
            }
        }
        merge(a, low, mid, high);
    }
}

int main()
{
    int n;
    printf("Array size:");
    scanf("%d", &n);
    printf("\nArray:");
    int a[n];
    for(int i = 0; i < n ; i++)
        scanf("%d", &a[i]);
    mergesort(a, 0, n - 1);
    printf("Sorted array:");
    for(int i = 0; i < n ; i++)
        printf("%d\t", a[i]);

    return 0;
}

