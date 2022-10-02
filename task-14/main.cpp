#include <stdio.h>
#include <omp.h>
#include <vector>
#include <cmath>

using namespace std;

int sqr(int num)
{
    int sqr_num = 0;
    #pragma omp parallel for reduction(+:sqr_num)
    for (int i=0; i<num; i++)
    {
        sqr_num += 2*i+1;
    }
    return sqr_num;
}

int main()
{
    int num = 210;
    int sqr_num = sqr(num);
    printf("Square of %d is %d\n", num, sqr_num);

    return 0;
}