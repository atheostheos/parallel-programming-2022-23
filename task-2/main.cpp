#include <stdio.h>
#include <omp.h>

void run_part()
{
    if (omp_get_max_threads() == 1)
    {
        return;
    }
    
    #pragma omp parallel if(omp_get_max_threads() > 1)
    {
        printf("Running code part: thread %d of %d\n", omp_get_thread_num(), omp_get_max_threads());
    }
}

int main()
{
    printf("Total nubmer of threads: %d\n", omp_get_max_threads());

    printf("Running w/ three thread\n");
    omp_set_num_threads(3);
    run_part();

    printf("Running w/ one thread\n");
    omp_set_num_threads(1);
    run_part();

    
    return 0;
}