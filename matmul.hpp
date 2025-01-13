#ifndef MATMUL_H
#define MATMUL_H
 void matrix_multiplication(int **A , int **B,int **C,int a_rows,int a_cols,int b_cols,int* timeTaken);
 void printArray(int** A,int row,int col);
 int compare(int** result,int ** C,int rows,int cols);
#endif