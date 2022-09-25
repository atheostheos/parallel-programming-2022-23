#include <stdio.h>
#include <omp.h>
#include <random>
#include <algorithm>

void print_array(int arr[], int size)
{
    for (int i=0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_matrix(int matrix[6][8])
{
    for (int i=0; i < 6; i++)
    {
        print_array(matrix[i], 8);
    }
    printf("\n");
}


float average(int matrix[6][8])
{
    int sum = 0;
    int count = 0;
    int h = 6;
    int w = 8;
    for (int i=0; i < h; i++) 
    {
        for (int j=0; j < w; j++)
        {
            sum += matrix[i][j];

            count += 1;
        }
    }
    return sum/count;
}

int get_edge_value(int matrix[6][8], bool max) 
{
    int h = 6;
    int w = 8;
    int edge_value = matrix[0][0];
    int cell;

    for (int i=0; i < 6; i++)
    {
        for (int j=0; j < 8; j++)
        {
            cell = matrix[i][j];
            if ((max && cell > edge_value) || (!max && cell < edge_value))
            {
                edge_value = cell;
            }
        }
    }
    return edge_value;
}

int count_thirds(int matrix[6][8])
{
    int count = 0;

    for (int i=0; i < 6; i++)
    {
        for (int j=0; j < 8; j++)
        {
            if (matrix[i][j] % 3 == 0) count += 1;
        }
    }

    return count;
}

int main()
{
    int matrix[6][8];
    int w = 8;
    int h = 6;
    for (int i=0; i < h; i++) 
    {
        for (int j=0; j < w; j++)
        {
            matrix[i][j] = (std::rand() % 10);
        }
    }
    printf("Matrix:\n");
    print_matrix(matrix);
    
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("Thread № %d\n", omp_get_thread_num());
            printf("Average: %.2f\n", average(matrix));
        }
        #pragma omp section
        {
            printf("Thread № %d\n", omp_get_thread_num());
            printf("Min: %d\n", get_edge_value(matrix, false));
            printf("Max: %d\n", get_edge_value(matrix, true));
        }
        #pragma omp section
        {
            printf("Thread № %d\n", omp_get_thread_num());
            printf("Divisible by 3: %d\n", count_thirds(matrix));
        }
    }
}