#include <iostream>
#include <iomanip>

// I use this to generate a copy of the original matrix, so that the
// functions dont modify it
double **generate_matrix(double **matrix, size_t rows, size_t columns)
{

  // first we declare the new matrix
  double **t_matrix = new double *[rows];
  for (int i{0}; i < rows; ++i)
    t_matrix[i] = new double[columns];

  // then we loop through it setting it to be equal to the original matrix
  for (int i{0}; i < rows; ++i)
  {
    for (int j{0}; j < columns; ++j)
    {
      t_matrix[i][j] = matrix[i][j];
    }
  }

  // then we return the original matrix
  return t_matrix;
}

// Here it is implemented the gaussian elimination algorithm that is used
//continuosly in the program
double **gaussian_elimination(double **t_matrix, size_t rows, size_t columns)
{

  //first we declare a array that is going to contain only one of the rows for future usage
  double *temp_array = new double[columns];
  bool is_swapped{false};
  double **matrix = generate_matrix(t_matrix, rows, columns);

  // here we start to loop through the columns, as it is easier then to go
  //through rows
  for (int k{0}; k < columns; k++)
  {
  // here we start to look for the first non 0 element in a column
  // if it is in the k'th row, we just leave it there, if it isnt, we move
  //this row into the k'th one, so that we dont have a 0 as a pivot.
    for (int i{k}; i < rows; ++i)
    {
      if (is_swapped)
      {
        is_swapped = false;
        break;
      }
      if (matrix[i][k] != 0)
      {
        temp_array = matrix[k];
        matrix[k] = matrix[i];
        matrix[i] = temp_array;
        temp_array = nullptr;
        is_swapped = true;
      }
    }
  //After that we simply get what number we need to multiply to the column
  // for it to cancel the value below it, and do the sum of rows:
    {
      double multiplier{};
      for (int i{k + 1}; i < rows; ++i)
      {
        multiplier = matrix[i][k] / matrix[k][k];
        for (int j{k}; j < columns; ++j)
        {
          matrix[i][j] -= matrix[k][j] * multiplier;
        }
      }
    }
  }

  delete[] temp_array;
  return matrix;
}

// This functions is used to do reverse gaussian elimination in augmented matrixes, so that we can
// find the inverse
double **retro_elimination(double **matrix, size_t rows, size_t columns)
{

  int iter_rows{rows - 1}, iter_columns{columns - 1};
  double multiplier{};
  int counter{};
  // here we check for every element that is on the same row and columns number
  // as those will always have zeros on its left and be 1, as this matrix
  // should already be gaussian eliminated, then we simply cancel all the 
  // rows above
  for (int i{iter_rows}; i > 0; --i)
  {
    for (int j{0}; j < columns; ++j)
    {
      if (i == j)
      {
        counter = i - 1;
        while (counter != -1)
        {
          multiplier = matrix[counter][j];
          for (int k{0}; k < columns; k++)
          {
            matrix[counter][k] -= matrix[i][k] * multiplier;
          }
          counter--;
        }
      }
    }
  }

  return matrix;
}

// this one simply finds the elements where the row number is equal to the column
// number, and we divide the entire row by this number, this is used on gaussian
// eliminated matrixes, as those always have 0's on the left, and are the ones
// we need to simplify to get to the inverse
double **simplify_rows(double **matrix, size_t rows, size_t columns)
{

  size_t min{};
  double divisor{};
  min = (rows < columns) ? rows : columns;

  for (int i{0}; i < min; i++)
  {
    divisor = matrix[i][i];
    for (int j{0}; j < columns; j++)
    {
      matrix[i][j] /= divisor;
    }
  }

  return matrix;
}

// this one simply finds the determinant
double determinant(double **t_matrix, size_t n)
{
  double determinant{1};
  double **matrix = generate_matrix(t_matrix, n, n);
  // gaussian elimination
  matrix = gaussian_elimination(matrix, n, n);


  // and then we multiply all the elements in the primary diagonal
  for (int i{0}; i < n; ++i)
  {
    determinant *= matrix[i][i];
  }

  return determinant;
}

// Here is the function used to find the inverse matrix
double **inverse(double **t_matrix, size_t n)
{

  // first we create the augmented_matrix, creating a
  // matrix with double the number of columns
  double **augmented_matrix = new double *[n];
  const size_t columns = 2 * n;
  const size_t &rows = n;

  for (int i{0}; i < rows; ++i)
    augmented_matrix[i] = new double[columns];

  // and the we fill if accodingly, so that we have
  // a correct augmented matrix
  for (int i{0}; i < rows; ++i)
  {
    for (int j{0}; j < columns; ++j)
    {
      if ((j) == (i + rows))
      {
        augmented_matrix[i][j] = 1;
      }
      else if (j < rows)
      {
        augmented_matrix[i][j] = t_matrix[i][j];
      }
      else
      {
        augmented_matrix[i][j] = 0;
      }
    }
  }

  // then we perform the operations to get the augmented matrix to have
  // the identity on the left
  augmented_matrix = gaussian_elimination(augmented_matrix, rows, columns);
  augmented_matrix = simplify_rows(augmented_matrix, rows, columns);
  augmented_matrix = retro_elimination(augmented_matrix, rows, columns);

  double **matrix = generate_matrix(t_matrix, rows, columns);

  // then we just grab the matrix formed on the right and return it.
  for (int i{0}; i < n; i++)
  {
    for (int j{0}; j < n; j++)
    {
      matrix[i][j] = augmented_matrix[i][j + n];
    }
  }

  return matrix;
}

// used to print matrices for easier visualization
void print_matrix(double **matrix, size_t rows, size_t columns)
{
  for (int i{0}; i < rows; ++i)
  {
    for (int j{0}; j < columns; ++j)
    {
      std::cout << std::setw(10) << matrix[i][j];
      if ((columns - 1) == j)
        std::cout << "\n";
    }
  }
}
