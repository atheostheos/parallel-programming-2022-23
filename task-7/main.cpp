#include <stdio.h>
#include <omp.h>

int main() {
    const int ARR_SIZE = 12;
    int a[12],
        b[12],
        c[12];

    omp_set_num_threads(3);
    printf("Num threads in ab cycle: %d\n", omp_get_max_threads());
    #pragma omp parallel for schedule(static, 3)
    for (int i=0; i<ARR_SIZE; i++) 
    {
        printf("   Index: %d, thread: %d, num threads: %d\n", i, omp_get_thread_num(), omp_get_num_threads());
        a[i] = i;
        b[i] = ARR_SIZE-i;
    }

    omp_set_num_threads(4);
    printf("Num threads in c cycle: %d\n", omp_get_max_threads());
    #pragma omp parallel for schedule(dynamic, 2)
    for (int i=0; i<ARR_SIZE; i++)
    {
        printf("   Index: %d, thread: %d, num threads: %d\n", i, omp_get_thread_num(), omp_get_num_threads());
        c[i] = a[i]+b[i];
    }

    return 0;
}