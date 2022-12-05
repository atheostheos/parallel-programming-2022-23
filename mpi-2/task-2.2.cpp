#include <mpi.h>
#include <stdio.h>
#include <random>
#include <cmath>

void fill_array(int arr[], int size) {
    for(int i = 0; i < size; i++) {
            arr[i] = (rand() % 10);
    }
}

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
        int a[arr_size];
        int b[arr_size];

        fill_array(a, arr_size);
        fill_array(b, arr_size);

        printf("Array a\n");
        for(int i = 0; i < arr_size; i++){
            printf("%d ", a[i]);
        }
        printf("\n");

        printf("Array b\n");
        for(int i = 0; i < arr_size; i++){
            printf("%d ", b[i]);
        }
        printf("\n");

        int chunk_size = arr_size / (world_size - 1);
        int leftover = arr_size - chunk_size * (world_size -1);

        printf("Chunk size %d, %d leftover number(s) will be sent to first process\n", chunk_size, leftover);
        

        for (int recevier_rank = 0; recevier_rank < world_size; recevier_rank++) {
            if (recevier_rank != rank)
            {
                if (recevier_rank == 1) {
                    printf("Sending chunk {%d, %d}\n", 0, chunk_size+leftover);
                    MPI_Send(&a, chunk_size+leftover, MPI_INT, recevier_rank, tag, MPI_COMM_WORLD);
                    MPI_Send(&b, chunk_size+leftover, MPI_INT, recevier_rank, tag, MPI_COMM_WORLD);
                } else {
                    int chunk_start = chunk_size*(recevier_rank-1)+leftover;
                    printf("Sending chunk {%d, %d}\n", chunk_start, chunk_start+chunk_size);
                    MPI_Send(&a[chunk_start], chunk_size, MPI_INT, recevier_rank, tag, MPI_COMM_WORLD);
                    MPI_Send(&b[chunk_start], chunk_size, MPI_INT, recevier_rank, tag, MPI_COMM_WORLD);
                }

            }
        }

        for (int recevier_rank = 0; recevier_rank < world_size; recevier_rank++) {
            if (recevier_rank != rank) 
            {
                MPI_Status status;
                if (recevier_rank == 1) {
                    printf("Received chunks w/ size %d from process %d\n", arr_size, recevier_rank);
                    MPI_Recv(&a, arr_size+leftover, MPI_INT, recevier_rank, tag, MPI_COMM_WORLD, &status);
                    MPI_Recv(&b, arr_size+leftover, MPI_INT, recevier_rank, tag, MPI_COMM_WORLD, &status);
                } else {
                    int chunk_start = chunk_size*(recevier_rank-1)+leftover;
                    printf("Received chunks w/ size %d from process %d\n", arr_size, recevier_rank);
                    MPI_Recv(&a[chunk_start], chunk_size, MPI_INT, recevier_rank, tag, MPI_COMM_WORLD, &status);
                    MPI_Recv(&b[chunk_start], chunk_size, MPI_INT, recevier_rank, tag, MPI_COMM_WORLD, &status);
                }
            }
        }

        printf("Array a\n");
        for(int i = 0; i < arr_size; i++){
            printf("%d ", a[i]);
        }
        printf("\n");

        printf("Array b\n");
        for(int i = 0; i < arr_size; i++){
            printf("%d ", b[i]);
        }
        printf("\n");
    }

    if (rank > 0)
    {
        MPI_Status status;
        // Probe for an incoming message from process zero
        MPI_Probe(0, tag, MPI_COMM_WORLD, &status);
        int arr_size;
        MPI_Get_count(&status, MPI_INT, &arr_size);

        printf("Process %d: received chuncks w/ size %d\n", rank, arr_size);

        // Allocate a buffer to hold the incoming numbers
        int x[arr_size];
        int y[arr_size];

        MPI_Recv(&x, arr_size, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        MPI_Recv(&y, arr_size, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

        MPI_Send(&y, arr_size, MPI_INT, 0, tag, MPI_COMM_WORLD);
        MPI_Send(&x, arr_size, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }

    // Finalize: Any resources allocated for MPI can be freed
    MPI_Finalize();
    return 0;
}
