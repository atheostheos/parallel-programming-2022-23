#include <stdio.h>
#include <omp.h>

int main() 
{
    const int ARR_SIZE = 10;
    int a[ARR_SIZE] = {11, 12, 13, 14, 15, 16, 17 ,18 ,19 ,110},
        b[ARR_SIZE] = {21, 22, 23, 24, 25, 26, 27, 28, 29 ,210},
        sum_a = 0,
        sum_b = 0;
    float av_a = 0,
          av_b = 0;

    #pragma omp parallel for reduction(+: sum_a, sum_b)
    for (int i=0; i<ARR_SIZE; i++)
    {
        sum_a += a[i];
        sum_b += b[i];
    }

    #pragma omp sections
    {
        #pragma omp section
        {
            av_a = sum_a/ARR_SIZE;
        }
        #pragma omp section
        {
            av_b = sum_b/ARR_SIZE;
        }
    }

    printf("Average value for array a: %.2f\n", av_a);
    printf("Average value for array b: %.2f\n", av_b);
    if (av_a > av_b) 
    {
        printf("Average of array a is higher\n");
    } else 
    {
        printf("Average of array b is higher\n");
    }

    return 0;
}