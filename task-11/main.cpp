#include <stdio.h>
#include <omp.h>
#include <vector>
#include "../utils/matrix.h"

using namespace std;

int main()
{
    const int ARRAY_LENGTH = 10;
    std::vector<int> arr = get_vector(ARRAY_LENGTH);

    int max_divseven = -1;

    #pragma omp parallel for 
    for (int i=0; i<ARRAY_LENGTH; i++)
    {
        if (arr[i]%7==0 && arr[i] > max_divseven)
        {
            #pragma omp critical
            {
                max_divseven = arr[i];
            }
        }
    }

    if (max_divseven < 0)
    {
        printf("No elements divisible by 7\n");
    } else {
        printf("Max divisible by seven: %d\n", max_divseven);
    }

    return 0;
}