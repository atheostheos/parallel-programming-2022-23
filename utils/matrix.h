#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <random>

const int RAND_LIMIT = 100;

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


#endif