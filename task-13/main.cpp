#include <stdio.h>
#include <omp.h>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    int arr_size = 30;
    int a[arr_size] = {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1};

    int dec_num = 0;
    #pragma omp parallel for reduction(+:dec_num)
    for (int i=0; i< arr_size; i++)
    {
        if (a[i] != 0)
        {
            int pow_dig = pow(2, i);
            dec_num += pow_dig;
            printf("Thread: %d, digit's value: %d\n", omp_get_thread_num(), pow_dig);
        }
    }

    printf("Number in decimal: %d\n", dec_num);

    return 0;
}