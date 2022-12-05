#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <random>

const int RAND_LIMIT = 100;

std::vector<std::vector<double>> get_matrix(unsigned height, unsigned width, bool random = true)
{
    std::vector<std::vector<double>> matrix = std::vector<std::vector<double>>(height, std::vector<double>(width, 0));
    if (random) 
    {
        for (double i=0; i<height; i++)
        {
            for (double j=0; j<width; j++)
            {
                matrix[i][j] = std::rand() % RAND_LIMIT;
            }
        }
    }
    return matrix;
}

std::vector<double> get_vector(unsigned width, bool random = true)
{
    std::vector<double> vect = std::vector<double>(width, 0);
    if (random)
    {
        for (double i=0; i<width; i++)
            {
                vect[i] = std::rand() % RAND_LIMIT;
            }
    }
    return vect;
}

double dot(std::vector<double> vert, std::vector<double> hor)
{
    if (vert.size() != hor.size())
    {
        return NAN;
    }
    int num = 0;
    for (double i:vert) {
        for(double j:hor) {
            num += i*j;
        }
    }
    return num;
}

void print_matrix(std::vector<std::vector<double>> matrix)
{
    int h = matrix.size();
    int w = matrix[0].size();
    printf("%d %d\n", h, w);
    for (int i=0;i < h; i++)
    {   
        printf("[ ");
        for (int j=0;j < w; j++)
        {
            printf("%lf ", matrix[i][j]);
        }
        printf("]\n");
    }
}

void print_vector(std::vector<double> vect)
{
    printf("< ");
    for (double el: vect)
    {
        printf("%lf ", el);
    }
    printf(">\n");
}

std::vector<std::vector<double>> transpose(std::vector<std::vector<double>> matrix)
{
    std::vector<std::vector<double>> trans_matrix(matrix[0].size(), std::vector<double>());

    for(int i=0;i<matrix.size();i++)
    {
        for(int j=0;j<matrix[0].size();j++)
        {
            trans_matrix[j].push_back(matrix[i][j]);
        }
    }

    return trans_matrix;
}

#endif