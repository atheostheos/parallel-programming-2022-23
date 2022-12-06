#include <stdio.h>
#include <mpi.h>
#include <random>

#define ROOT 0
#define n    101
#define TAG  0

int main(int argc, char** argv) {
    int rank;
    int world_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int part = n % world_size == 0 ? n / world_size : n / world_size + 1;
    int y[part];
    int x[n];

    if (rank == ROOT) {
        for (int i = 0; i < n; i++) {
            x[i] = rand() % 100;
            printf("%d ", x[i]);
        }
        printf("\n");
    }

    MPI_Scatter(&x[rank*part], part, MPI_INT, &y[0], part, MPI_INT, ROOT, MPI_COMM_WORLD);

    int sum_part = 0;
    for (int i = 0; i < part && rank * part + i < n; ++i) {
        sum_part += abs(y[i]);
    }
    printf("%d\n", sum_part);

    int sum;
    MPI_Reduce(&sum_part, &sum, 1, MPI_INT, MPI_SUM, ROOT, MPI_COMM_WORLD);

    if (rank == ROOT) {
        printf("||x||=%d\n", sum);
    }

    MPI_Finalize();
    return 0;
}