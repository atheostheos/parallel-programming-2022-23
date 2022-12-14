#include <stdio.h>
#include <mpi.h>
#include <random>
#include "utils.h"

#define ROOT 0
#define TAG  0
#define M_A  4
#define N_A  3
#define M_B  M_A
#define N_B  N_A

int main(int argc, char** argv) {
    int rank;
    int world_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int part = M_A % world_size == 0 ? M_A / world_size : M_A / world_size + 1;
    int A[M_A][N_A];
    int B[M_B][N_B];
    int Ap[part][N_A];
    int Bp[part][N_B];

    if (rank == ROOT) {
        for (int i = 0; i < M_A; i++) {
            for (int j=0; j < N_A; j++) {
                B[i][j] = rand() % 10;
                A[i][j] = rand() % 10;
            }
        }

        printf("Array A:\n");
        for (int i=0; i< M_A; i++)
        {
            print_array(A[i], N_A);
        }
        printf("Array B:\n");
        for (int i=0; i< M_B; i++)
        {
            print_array(B[i], N_B);
        }
    }

    MPI_Scatter(&A[rank*part][0], part*N_A, MPI_INT, &Ap[0][0], part*N_A, MPI_INT, ROOT, MPI_COMM_WORLD);
    MPI_Scatter(&B[rank*part][0], part*N_B, MPI_INT, &Bp[0][0], part*N_B, MPI_INT, ROOT, MPI_COMM_WORLD);

    int Cp[part][N_A];
    for (int i = 0; i < part && rank * part + i < M_A; ++i) {
        for (int j = 0; j < N_A; ++j) {
            Cp[i][j] = Ap[i][j]*Bp[i][j];
        }
    }

    int C[M_A][N_A];
    MPI_Gather(&Cp[0][0], part*N_A, MPI_INT, &C[rank*part][0], part*N_A, MPI_INT, ROOT, MPI_COMM_WORLD);

    if (rank == ROOT) {
        printf("Array C = A x B:\n");
        for (int i = 0; i < M_A; ++ i) {
            print_array(C[i], N_A);
        }
    }

    MPI_Finalize();
    return 0;
}