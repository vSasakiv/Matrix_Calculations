#include <iostream>
#include <iomanip>
#include "matrix_operations.hh"

void print_matrix(double **matrix, size_t rows, size_t columns);
double **gaussian_elimination(double **matrix, size_t rows, size_t columns);
double determinant(double **matrix, size_t n);
double **inverse(double **matrix, size_t n);

int main()
{

  size_t rows{}, columns{}, option{0};
  double matrix_determinant{};
  bool go_on{1};

  std::cout << std::setprecision(5);
  std::cout << "Input the amount of rows in the Matrix: ";
  std::cin >> rows;
  std::cout << "Input the amount of columns in the Matrix: ";
  std::cin >> columns;

  //  declaring the matrix as a pointer pointing to an array of pointers
  double **matrix = new double *[rows];
  for (int i{0}; i < rows; ++i)
    matrix[i] = new double[columns];

  // adding the value of the elements
  for (int i{0}; i < rows; ++i)
  {
    for (int j{0}; j < columns; ++j)
    {
      std::cout << "Insert the element in row " << i + 1 << " and column " << j + 1 << ": ";
      std::cin >> matrix[i][j];
    }
  }

  std::cout << "\nMatrix: \n";
  print_matrix(matrix, rows, columns);

  if (rows == columns)
  {
    size_t n{rows};
    while (go_on)
    {
      std::cout << "What would you like to do?\n";
      std::cout << "1 - Find the determinant\n";
      std::cout << "2 - Find the inverse matrix\n";
      std::cout << "3 - Find the triangular matrix\n";
      std::cout << "0 - Exit\n";
      std::cin >> option;

      switch (option)
      {
      case 0:
        go_on = false;
        std::cout << "Program ending...\n";
        break;
      case 1:
        std::cout << "The Determinant is equal to: " << determinant(matrix, n) << "\n";
        break;
      case 2:
        if (determinant(matrix, n) == 0)
        {
          std::cout << "This matrix does not have a inverse.\n";
        }
        else
        {
          std::cout << "The inverse matrix is: \n";
          print_matrix(inverse(matrix, n), n, n);
        }
        break;
      case 3:
        std::cout << "The triangular matrix is: \n";
        print_matrix(gaussian_elimination(matrix, n, n), n, n);
        break;
      default:
        std::cout << "Option not found.\n";
        break;
      }
    }
  }
  else
  {
    while (go_on)
    {
      std::cout << "What would you like to do?\n";
      std::cout << "1 - Find the triangular matrix\n";
      std::cout << "0 - Exit\n";
      std::cin >> option;

      switch (option)
      {
      case 0:
        go_on = false;
        std::cout << "Program ending...\n";
        break;
      case 1:
        std::cout << "The triangular matrix is: \n";
        print_matrix(gaussian_elimination(matrix, rows, columns), rows, columns);
        break;
      default:
        std::cout << "Option not found.\n";
        break;
      }
    }
  }

  // double **inverse_matrix = new double *[rows];
  // for (int i{0}; i < rows; ++i)
  //   inverse_matrix[i] = new double[columns*2];

  // inverse_matrix = inverse(matrix, rows);
  // print_matrix(inverse_matrix, rows, columns);

  return 0;
}
