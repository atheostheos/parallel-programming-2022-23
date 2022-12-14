#include <stdio.h>
#include <climits>
#include <mpi.h>
#include <random>
#include "utils.h"

#define ROOT 0
#define TAG  0
#define M_A  4
#define N_A  3

int main(int argc, char** argv) {
    int rank;
    int world_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int part = M_A % world_size == 0 ? M_A / world_size : M_A / world_size + 1;
    int A[M_A][N_A];
    int Ap[part][N_A];

    if (rank == ROOT) {
        for (int i = 0; i < M_A; i++) {
            for (int j=0; j < N_A; j++) {
                A[i][j] = rand() % 10;
            }
        }

        printf("Array A:\n");
        for (int i=0; i< M_A; i++)
        {
            print_array(A[i], N_A);
        }
    }

    MPI_Scatter(&A[rank*part][0], part*N_A, MPI_INT, &Ap[0][0], part*N_A, MPI_INT, ROOT, MPI_COMM_WORLD);

    // init empty array
    int sum;
    int max_part = INT_MIN;
    // cacluate parts of multiplication vectors
    for (int i = 0; i < part && rank * part + i < M_A; ++i) {
        int sum = 0;
        for (int j = 0; j < N_A; ++j) {
            sum += Ap[i][j];
        }
        sum = sum > 0 ? sum : -sum;
        max_part = sum > max_part ? sum : max_part;
    }


    int max;
    MPI_Reduce(&max_part, &max, 1, MPI_INT, MPI_MAX, ROOT, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("||A|| = %d\n", max);
    }

    MPI_Finalize();
    return 0;
}