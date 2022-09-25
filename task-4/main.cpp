#include <stdio.h>
#include <omp.h>
#include <algorithm>

void print_array(int arr[], int size)
{
    for (int i=0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("Array a: \n");
    print_array(a, 10);
    printf("Array b: \n");
    print_array(b, 10);

    omp_set_num_threads(2);
    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        switch (thread_num)
        {
            case 0:
                {
                    int *min = std::min_element( std::begin(a), std::end(a));
                    printf("Min for a: %d\n", *min);
                    break;
                }
            case 1:
                {
                    int *max = std::max_element( std::begin(b), std::end(b));
                    printf("Max for b: %d\n", *max);
                    break;
                }
            default:
                printf("Leftover thread %d\n", omp_get_thread_num());
        }
    }
    return 0;
}