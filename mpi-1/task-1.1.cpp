#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    printf("Hello, World!\n");

    // Finalize: Any resources allocated for MPI can be freed
    MPI_Finalize();
    return 0;
}
