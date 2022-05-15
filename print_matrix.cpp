#include <iostream>
#include <iomanip>
#include "matrix_operations.hh"

void print_matrix(double **matrix, size_t n)
{
  for (int i{0}; i < n; ++i)
  {
    for (int j{0}; j < n; ++j)
    {
      std::cout << std::setw(10) << matrix[i][j];
      if ((n - 1) == j)
        std::cout << "\n";
    }
  }
}
