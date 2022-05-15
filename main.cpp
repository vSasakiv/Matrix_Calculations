#include <iostream>
#include <iomanip>
#include "matrix_operations.hh"

void print_matrix(double **matrix, size_t n);

int main(){

  size_t n {};

  std::cout << std::setprecision(5);
  std::cout << "Input the size of the nxn Array (n): ";
  std::cin >> n;

  //  declaring the matrix as a pointer pointing to an array of pointers
  double **matrix = new double *[n];
  for (int i{0}; i < n; ++i)
    matrix[i] = new double[n];

  // adding the value of the elements
  for (int i{0}; i < n; ++i)
  {
    for (int j{0}; j < n; ++j)
    {
      std::cout << "Insert the element in row " << i + 1 << " and column " << j + 1 << ": ";
      std::cin >> matrix[i][j];
    }
  }
  // std::cout << "\n\n" << "Matrix: \n";
  print_matrix(matrix, n);

  return 0;
}


