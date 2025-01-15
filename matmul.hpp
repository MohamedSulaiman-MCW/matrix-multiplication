#ifndef MATMUL_H
#define MATMUL_H
 void matrix_multiplication(double **A , double **B,double **C,int a_rows,int a_cols,int b_cols,int* timeTaken);
 void printArray(double** A,int row,int col);
 int compare(double** result,double ** C,int rows,int cols);
#endif