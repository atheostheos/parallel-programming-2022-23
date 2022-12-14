#include <stdio.h>
#include <mpi.h>
#include <random>
#include "utils.h"

#define ROOT 0
#define TAG  0
#define M_A  6
#define N_A  3
#define N_B  M_A

int main(int argc, char** argv) {
    int rank;
    int world_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int part = M_A % world_size == 0 ? M_A / world_size : M_A / world_size + 1;
    int A[M_A][N_A];
    int b[N_B];
    int Ap[part][N_A];

    if (rank == ROOT) {
        for (int i = 0; i < N_B; i++) {
            b[i] = rand() % 10;
        }
        for (int i = 0; i < M_A; i++) {
            for (int j=0; j < N_A; j++) {
                A[i][j] = rand() % 10;
            }
        }

        printf("Array b:\n");
        print_array(b, N_B);

        printf("Array A:\n");
        for (int i=0; i< M_A; i++)
        {
            print_array(A[i], N_A);
        }
    }


    MPI_Bcast(&b[0], N_B, MPI_INT, ROOT, MPI_COMM_WORLD);
    MPI_Scatter(&A[rank*part][0], part*N_A, MPI_INT, &Ap[0][0], part*N_A, MPI_INT, ROOT, MPI_COMM_WORLD);

    // init empty array
    int mult_part[N_A];
    for (int i=0; i < N_A; i++)
    {
        mult_part[i] = 0;
    }
    // cacluate parts of multiplication vectors
        for (int i = 0; i < part && rank * part + i < M_A; ++i) {
            for (int j = 0; j < N_A; ++j) {
                mult_part[j] += b[rank * part + i]*Ap[i][j];
            }
    }


    int mult[part];
    MPI_Reduce(&mult_part[0], &mult[0], N_A, MPI_INT, MPI_SUM, ROOT, MPI_COMM_WORLD);

    if (rank == ROOT) {
        printf("bxA=\n");
        for (int j = 0; j < N_A; ++ j) {
            printf("%d ", mult[j]);
        } 
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}