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

    if (rank == 0) 
    {
        int arr_size = 10;
        int arr[arr_size];
        for(int i = 0; i < arr_size; i++){
            arr[i] =  (rand() % 10);
        }
        for (int recevier_rank = 0; recevier_rank < world_size; recevier_rank++) {
            if (recevier_rank != rank)
            {
                MPI_Send(&arr, arr_size, MPI_INT, recevier_rank, tag, MPI_COMM_WORLD);
            }
        }
    }

    if (rank > 0)
    {
        MPI_Status status;
        // Probe for an incoming message from process zero
        MPI_Probe(0, tag, MPI_COMM_WORLD, &status);
        int arr_size;
        MPI_Get_count(&status, MPI_INT, &arr_size);

        // Allocate a buffer to hold the incoming numbers
        int arr[arr_size];

        MPI_Recv(&arr, arr_size, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        printf("Process %d:\n", rank);
        for(int i = 0; i < arr_size; i++){
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    // Finalize: Any resources allocated for MPI can be freed
    MPI_Finalize();
    return 0;
}
