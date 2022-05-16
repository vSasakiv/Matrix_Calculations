#ifdef _Matrix_Ops_HH_
#define _Matrix_Ops_HH_
double determinant(double **matrix, size_t n);
double print_matrix(double **matrix, size_t rows, size_t columns);
double **gaussian_elemination(double **matrix, size_t rows, size_t columns);
double **inverse(double **matrix, size_t n);
#endif // _Determinant_HH
