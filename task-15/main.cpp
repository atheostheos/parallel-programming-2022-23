#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <vector>
#include <cmath>

using namespace std;

void print_vector(std::vector<int> vector)
{
    for (int i=0; i<vector.size(); ++i)
    std::cout << vector[i] << ' ';
}

std::vector<int> find_primes(int begin, int end)
{
    std::vector primes = std::vector<int>();
    bool sieve[end];
    // initialize array
    #pragma omp parallel for
    for (int i=0; i<end; i++)
    {
        sieve[i] = true;
    }

    int num;
    for (int i=1; i<end; i++)
    {
        num = i+1;
        if (sieve[i])
        {
            if (begin <= num && num <= end)
                primes.push_back(num);
            #pragma omp parallel for
            for (int j=i;j<end; j+= num)
            {
                sieve[j] = false;
            }
        }
    }

    return primes;
}

int main()
{
    int begin;
    int end;

    std::cout << "Enter section's start : ";
    std::cin >> begin;
    std::cout << "Enter section's end: ";
    std::cin >> end;
    
    std::cout << "Primes in section: " << std::endl;
    print_vector(find_primes(begin, end));
    std::cout << std::endl;

    return 0;
}