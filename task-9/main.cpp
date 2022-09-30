#include <stdio.h>
#include <omp.h>
#include <vector>
#include "../utils/matrix.h"

using namespace std;

int main()
{
    const int MATRIX_HEIGHT = 6;
    const int MATRIX_WIDTH = 8;

    std::vector<std::vector<int>> arr = get_matrix(MATRIX_HEIGHT, MATRIX_WIDTH);

    int max = arr[0][0];
    int min = arr[0][0];
    #pragma omp parallel for
    for (int i=0; i < MATRIX_HEIGHT; i++)
    {
        for (int j=0; j < MATRIX_WIDTH; j++)
        {
            if (arr[i][j] > max)
            {
                #pragma omp critical
                {
                    max = arr[i][j];
                }
            } else if (arr[i][j] < min)
            {
                #pragma omp critical
                {
                    min = arr[i][j];
                }
            }
        }
    }

    printf("Max value: %d\n", max);
    printf("Min value: %d\n", min);

    return 0;
}