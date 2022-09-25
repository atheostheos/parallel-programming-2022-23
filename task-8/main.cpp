#include <stdio.h>
#include <omp.h>
#include <vector>
#include <random>
#include <stdexcept>
#include <chrono>
#include <iostream>

using namespace std;


const int MATRIX_HEIGHT = 1000000;
const int MATRIX_WIDTH = 10;
const int RAND_LIMIT = 5;

std::vector<std::vector<int>> get_matrix(unsigned height, unsigned width, bool random = true)
{
    std::vector<std::vector<int>> matrix = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
    if (random) 
    {
        for (int i=0; i<height; i++)
        {
            for (int j=0; j<width; j++)
            {
                matrix[i][j] = std::rand() % RAND_LIMIT;
            }
        }
    }
    return matrix;
}

std::vector<int> get_vector(unsigned width, bool random = true)
{
    std::vector<int> vect = std::vector<int>(width, 0);
    if (random)
    {
        for (int i=0; i<width; i++)
            {
                vect[i] = std::rand() % RAND_LIMIT;
            }
    }
    return vect;
}

std::vector<int> dot_vect_matrix(std::vector<int> vect, std::vector<std::vector<int>> matrix)
{
    if (vect.size() != matrix.size())
    {
        throw std::invalid_argument("Vector width must match matrix height");
    }

    int width = matrix[0].size();

    std::vector<int> result = std::vector<int>(width, 0);
    for (int i=0; i<width; i++) {
        for (int j=0; j<vect.size(); j++) {
            result[i] += vect[j]*matrix[j][i];
        }
    }

    return result;
}

std::vector<int> dot_vect_matrix_mp(std::vector<int> vect, std::vector<std::vector<int>> matrix)
{
    if (vect.size() != matrix.size())
    {
        throw std::invalid_argument("Vector width must match matrix height");
    }

    int width = matrix[0].size();

    std::vector<int> result = std::vector<int>(width, 0);
    
    #pragma omp parallel for
    for (int i=0; i<width; i++) {
        //  calculate in parallel for each cell
        int cell = 0;
        for (int j=0; j<vect.size(); j++) {
            cell += vect[j]*matrix[j][i];
        }
        result[i] = cell;
    }

    return result;
}



int main() {
    std::vector<std::vector<int>> matrix = get_matrix(MATRIX_HEIGHT, MATRIX_WIDTH);
    std::vector<int> vect = get_vector(MATRIX_HEIGHT);
    std::vector<int> result;

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    
    begin = std::chrono::steady_clock::now();
    result = dot_vect_matrix(vect, matrix);
    end = std::chrono::steady_clock::now();
    std::cout << "Non parallel. Result: ";
    for (int i: result)
        std::cout << i << ' '; 
    std::cout << std::endl;
    std::cout << "Time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    begin = std::chrono::steady_clock::now();
    result = dot_vect_matrix_mp(vect, matrix);
    end = std::chrono::steady_clock::now();
    std::cout << "Parallel. Result: ";
    for (int i: result)
        std::cout << i << ' '; 
    std::cout << std::endl;
    std::cout << "Time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    return 0;
}