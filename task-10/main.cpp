#include <stdio.h>
#include <omp.h>
#include <vector>
#include "../utils/matrix.h"

using namespace std;

int main()
{
    const int ARRAY_LENGTH = 30;
    std::vector<int> arr = get_vector(ARRAY_LENGTH);

    int count = 0;
    #pragma omp parallel for 
    for (int i=0; i<ARRAY_LENGTH; i++) 
    {
        if (arr[i] % 9 == 0)
        {
            #pragma omp atomic
            count++;
        }
    }

    printf("Amount of elements divisible by 9: %d\n", count);

    return 0;
}
