#include<iostream>
#include<chrono>
#include <math.h>
using namespace std;
using namespace std::chrono;

void printArray(double** matrix,int row,int col){
    for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
}

//function to reset the result matrix 
void resetMatrix(double** matrix, int row, int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            matrix[i][j] = 0;
        }
    }
}

// ijk loop order
auto multiply_ijk(double** A, double** B, double** C, int m, int n, int p) {
    resetMatrix(C,m,p);
    auto start=high_resolution_clock::now();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    auto end=high_resolution_clock::now();
    auto duration=duration_cast<microseconds>(end-start);
    cout << "Time taken by ijk loop is " << duration.count()<<" microseconds\n\n";
    return duration.count();
}

// ikj loop order
auto multiply_ikj(double** A, double** B, double** C, int m, int n, int p) {
    resetMatrix(C,m,p);
    auto start=high_resolution_clock::now();
    for (int i = 0; i < m; ++i) {
        for (int k = 0; k < n; ++k) {
            for (int j = 0; j < p; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    auto end=high_resolution_clock::now();
    auto duration=duration_cast<microseconds>(end-start);
    cout << "Time taken by ikj loop is " << duration.count()<<" microseconds\n\n";
    return duration.count();
}

// jik loop order
auto multiply_jik(double** A, double** B, double** C, int m, int n, int p) {
    resetMatrix(C,m,p);
    auto start=high_resolution_clock::now();
    for (int j = 0; j < p; ++j) {
        for (int i = 0; i < m; ++i) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    auto end=high_resolution_clock::now();
    auto duration=duration_cast<microseconds>(end-start);
    cout << "Time taken by jik loop is " << duration.count()<<" microseconds\n\n";
    return duration.count();
}

// jki loop order
auto multiply_jki(double** A, double** B, double** C, int m, int n, int p) {
    resetMatrix(C,m,p);
    auto start=high_resolution_clock::now();
    for (int j = 0; j < p; ++j) {
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < m; ++i) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    auto end=high_resolution_clock::now();
    auto duration=duration_cast<microseconds>(end-start);
    cout << "Time taken by jki loop is " << duration.count()<<" microseconds\n\n";
    return duration.count();
}

// kij loop order
auto multiply_kij(double** A, double** B, double** C, int m, int n, int p) {
    resetMatrix(C,m,p);
    auto start=high_resolution_clock::now();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < p; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    auto end=high_resolution_clock::now();
    auto duration=duration_cast<microseconds>(end-start);
    cout << "Time taken by kij loop is " << duration.count()<<" microseconds\n\n";
    return duration.count();
}

// kji loop order
auto multiply_kji(double** A, double** B, double** C, int m, int n, int p) {
    resetMatrix(C,m,p);
    auto start=high_resolution_clock::now();
    for (int k = 0; k < n; ++k) {
        for (int j = 0; j < p; ++j) {
            for (int i = 0; i < m; ++i) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    auto end=high_resolution_clock::now();
    auto duration=duration_cast<microseconds>(end-start);
    cout << "Time taken by kji loop is " << duration.count()<<" microseconds\n\n";
    return duration.count();
}

//function to compare two given matrices
int compare(double** result,double ** C,int rows,int cols){
    const double epsilon = 1e-9;

    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            double diff = fabs(result[i][j] - C[i][j]);
            double scale = fmax(fabs(result[i][j]), fabs(C[i][j])); // Using max for relative comparison
            double absolute_epsilon = epsilon * scale;
            if(diff>absolute_epsilon){
                cout << result[i][j] <<" "<<C[i][j];
                return 0;
            }
        }
    }
    return 1;
}

void matrix_multiplication(double **A , double **B , double **C ,int a_rows,int a_cols,int b_cols,int* timeTaken){
    timeTaken[0]=multiply_ijk(A,B,C,a_rows,a_cols,b_cols);
    timeTaken[1]=multiply_ikj(A,B,C,a_rows,a_cols,b_cols);
    timeTaken[2]=multiply_jik(A,B,C,a_rows,a_cols,b_cols);
    timeTaken[3]=multiply_jki(A,B,C,a_rows,a_cols,b_cols);
    timeTaken[4]=multiply_kij(A,B,C,a_rows,a_cols,b_cols);
    timeTaken[5]=multiply_kji(A,B,C,a_rows,a_cols,b_cols);
    return;
}

