#include <stdio.h>
#include <omp.h>

int main()
{
    int a = 1;
    int b = 1;

    printf("Before 1st operation:\n a = %d\n b = %d\n", a, b);
    #pragma omp dynamic(2) private(a) firstprivate(b)
    {
        int thread_num = omp_get_thread_num() + 1;
        printf("On thread %d\n", thread_num);
        a += thread_num;
        b += thread_num;
        printf("In 1st operation after increment:\n a = %d\n b = %d\n", a, b);
    }
    printf("After 1st operation:\n a = %d\n b = %d\n", a, b);


    printf("Before 2nd operation:\n a = %d\n b = %d\n", a, b);
    #pragma omp dynamic(4) shared(a) private(b)
    {
        int thread_num = omp_get_thread_num() + 1;
        printf("On thread %d\n", thread_num);
        a -= thread_num;
        b -= thread_num;
        printf("In 2nd operation after increment:\n a = %d\n b = %d\n", a, b);
    }
    printf("After 2nd operation:\n a = %d\n b = %d\n", a, b);
}