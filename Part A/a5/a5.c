//Write an OpenMP parallel program for Points Classification. Prove the correctness of sequential program with that of parallel.
//Clustering
#include<stdio.h>
#include<omp.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

#define no_of_clusters  4
int cluster_centers[no_of_clusters][2] = {{20, 20},{60,60},{20,60},{60,20}};
int no_of_points = 9;
int datapoints[100][2];
int cluster[no_of_clusters];

void distribute_points() //distributes points in the x-y plane
{
    int upper = 100, lower = 0;
    #pragma omp parallel for num_threads(8)
    {
       for(int i = 0; i < no_of_points; i++)
    {
        datapoints[i][0] = (rand() % (upper - lower + 1)) + lower;
        datapoints[i][1] = (rand() % (upper - lower + 1)) + lower;
    }
    }
}

double get_distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));  //get Euclidean distance between datapoint and cluster center
}

void cluster_points()
{
    int min_dist, i, j;
    double dist;
    int cluster_index;

    #pragma omp parallel for num_threads(8) private(cluster_index, i, j, dist, min_dist)
    {
        for(i = 0; i < no_of_points; i++)
    {
        min_dist = 999;
        dist = 0;
        for(j = 0; j < no_of_clusters; j++)
        {
            dist = get_distance(datapoints[i][0], datapoints[i][1], cluster_centers[j][0], cluster_centers[j][1]);
            if(dist < min_dist)
            {
                min_dist = dist;
                cluster_index = j;
            }
        }
        printf("\nPoint: (%d, %d) in cluster: (%d, %d)", datapoints[i][0], datapoints[i][1], cluster_centers[cluster_index][0], cluster_centers[cluster_index][1]);
        cluster[cluster_index]++;
    }
    }
}

void main()
{
    distribute_points();
    //double start_time = omp_get_wtime();
    cluster_points();
    //double time_taken = omp_get_wtime() - start_time;
    //printf("Time taken : %f", time_taken);
    printf("\n");
    for(int i = 0; i < no_of_clusters; i++)
        printf("CLuster: (%d, %d) -> %d\n", cluster_centers[i][0], cluster_centers[i][1], cluster[i]);
}

