#include <mpi.h>
#include <stdio.h>
#include <random>

int main(int argc, char **argv)
{
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
  
    // Get the number of processes ssociated with the communicator
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the calling process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int tag = 1;
    MPI_Status status;

    int arr_size = 10;
    int arr[arr_size];
    if (rank == 0) 
    {
        for(int i = 0; i < arr_size; i++){
            arr[i] =  (rand() % 10);
        }
        MPI_Send(&arr, arr_size, MPI_INT, 1, tag, MPI_COMM_WORLD);
    }

    if (rank == 1)
    {
        MPI_Recv(&arr, arr_size, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        for(int i = 0; i < arr_size; i++){
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    // Finalize: Any resources allocated for MPI can be freed
    MPI_Finalize();
    return 0;
}
