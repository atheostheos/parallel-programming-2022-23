#include <mpi.h>
#include <stdio.h>
#include <random>
#include <cmath>
#include "utils.h"

using namespace std;

#define SENDER 0
#define TAG    1
#define M_A    3
#define N_A    4
#define M_B    M_A
#define N_B    N_A

void start_sender() {
   int world_size;
   MPI_Comm_size(MPI_COMM_WORLD, &world_size);

   vector<vector<double>> A = get_matrix(M_A, N_A);
   vector<vector<double>> B = get_matrix(M_B, N_B);

   printf("Matrix A:\n");
   print_matrix(A);
   printf("Matrix B:\n");
   print_matrix(B);

   int chunk_size = M_A / (world_size - 1);
   int leftover = M_A - chunk_size * (world_size -1);
   int n_a = N_A;
   int n_b = N_B;

   // send data
   for (int t=1; t < world_size; t++) 
   {
      int start;
      int size;
      if (t == 1) 
      {
         start = 0;
         size = chunk_size + leftover ;
      } else {
         start = t*chunk_size-1 + leftover;
         size = chunk_size;
      }

      MPI_Send(&size, 1, MPI_INT, t, TAG, MPI_COMM_WORLD);
      MPI_Send(&n_a, 1, MPI_INT, t, TAG, MPI_COMM_WORLD);

      int end = start + size;
      for (int i = start; i < end; i++) 
      {
         MPI_Send(&A[i][0], N_A, MPI_DOUBLE, t, TAG, MPI_COMM_WORLD);
         MPI_Send(&B[i][0], N_A, MPI_DOUBLE, t, TAG, MPI_COMM_WORLD);
      }
   }

   // receive data
   vector<vector<double>> C = get_matrix(M_A, N_B);
   MPI_Status status;
   for (int t=1; t < world_size; t++) 
   {
      int start;
      int size;
      int end;
      if (t == 1) 
      {
         start = 0;
         size = chunk_size + leftover;
      } else {
         start = t*chunk_size-1 + leftover;
         size = chunk_size;
      }
      end = start + size;

      for (int i = start; i < end; i++) {
         MPI_Recv(&C[i][0], N_B, MPI_DOUBLE, t, TAG+t, MPI_COMM_WORLD, &status);
      }
   }
   printf("Multiplication:\n");
   print_matrix(C);
}

void start_receiver(int rank) {
   MPI_Status status;
   int size;
   int n_a;

   MPI_Recv(&size, 1, MPI_INT, SENDER, TAG, MPI_COMM_WORLD, &status);
   MPI_Recv(&n_a, 1, MPI_INT, SENDER, TAG, MPI_COMM_WORLD, &status);
   vector<vector<double>> A = get_matrix(size, n_a);
   vector<vector<double>> B = get_matrix(size, n_a);
   for (int i=0; i< size; i++) {
      MPI_Recv(&A[i][0], n_a, MPI_DOUBLE, SENDER, TAG, MPI_COMM_WORLD, &status);
      MPI_Recv(&B[i][0], n_a, MPI_DOUBLE, SENDER, TAG, MPI_COMM_WORLD, &status);
   }

   vector<vector<double>> C = get_matrix(size, n_a);
   for (int i=0; i<size; i++)
   {
      for (int j=0; j<n_a; j++) {
         C[i][j] = A[i][j] * B[i][j];
      }
   }
   
   for (vector<double> line: C) {
      MPI_Send(&line[0], n_a, MPI_DOUBLE, SENDER, TAG+rank, MPI_COMM_WORLD);
   }
}

int main(int argc, char **argv) {
   int rank;
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   if (rank == SENDER) 
   {
      start_sender();
   }
   
   if (rank != SENDER) 
   {
      start_receiver(rank);
   }

   MPI_Finalize();
   return 0;
}