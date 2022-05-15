#include <iostream>
#include "matrix_operations.hh"

double determinant(double **matrix, size_t n)
{

  //size_t n{};
  bool is_zero{true};
  double determinant{1};
  double *temp_array = new double[n];

  //std::cout << std::setprecision(5);
  //std::cout << "Input the size of the nxn Array (n): ";
  //std::cin >> n;
  /*
  // declaring the matrix as a pointer pointing to an array of pointers
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
  //std::cout << "\n\n" << "Matrix: \n";
  print_matrix(matrix, n);
  //std::cout << "\n\n" << "Reduced Matrix: \n";
  */
  // gaussian elimination

  // verifying if the elements of the first column are 0's

  for(int k{0} ; k < n ; k++){
    is_zero = true;
    for (int i{k}; i < n && is_zero; ++i)
    {
      if (matrix[i][k] != 0)
      {
        if (i == 0){
          is_zero = false;
          break;
        }
        temp_array = matrix[k];
        matrix[k] = matrix[i];
        matrix[i] = temp_array;
        temp_array = nullptr;
        is_zero = false;
      }
    }

    if (is_zero){
      std::cout << "The determinant is equal to zero \n";
      return 0;
    }
/*
    if (matrix[k][k] != 1){
      double divisor{matrix[k][k]};
      determinant_multiplier /= divisor;
      for (int j{0}; j < n; ++j){
        matrix[k][j] /= divisor;
      }
    }
*/
    {
      double multiplier {};
      for (int i{k + 1}; i < n; ++i){
        multiplier = matrix[i][k] / matrix[k][k];
        for (int j{k}; j < n; ++j){
          matrix[i][j] -= matrix[k][j] * multiplier;
        }
      }
    }
  }

  //print_matrix(matrix, n);

  for(int i {0} ; i < n ; ++i){
    determinant *= matrix[i][i];
  }

  std::cout << "\n" << "Determinant: " << determinant << std::endl;

  delete [] temp_array;
  for (int i{0}; i < n; ++i)
    delete [] matrix[i];
  delete [] matrix;

  return determinant;
}

