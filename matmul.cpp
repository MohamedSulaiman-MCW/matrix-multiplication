#include<iostream>
#include<chrono>
using namespace std;
using namespace std::chrono;
void printArray(int** matrix,int row,int col){
    for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
}
void resetMatrix(int** matrix, int row, int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            matrix[i][j] = 0;
        }
    }
}
// ijk loop order
void multiply_ijk(int** A, int** B, int** C, int m, int n, int p) {
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
    // printArray(C,m,p);
}

// ikj loop order
void multiply_ikj(int** A, int** B, int** C, int m, int n, int p) {
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
    // printArray(C,m,p);
}

// jik loop order
void multiply_jik(int** A, int** B, int** C, int m, int n, int p) {
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
    // printArray(C,m,p);
}

// jki loop order
void multiply_jki(int** A, int** B, int** C, int m, int n, int p) {
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
    // printArray(C,m,p);
}

// kij loop order
void multiply_kij(int** A, int** B, int** C, int m, int n, int p) {
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
    // printArray(C,m,p);
}

// kji loop order
void multiply_kji(int** A, int** B, int** C, int m, int n, int p) {
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
    // printArray(C,m,p);
}
void matrix_multiplication(int **A , int **B , int **C ,int a_rows,int a_cols,int b_cols){
    // cout << "inside the function";
    // for(int i=0;i<a_rows;i++){
    //     for(int j=0;j<b_cols;j++){
    //         C[i][j]=0;
    //         for(int k=0;k<a_cols;k++){
    //             C[i][j]+=A[i][k]*B[k][j];
    //         }
    //     }
    // }
    multiply_ijk(A,B,C,a_rows,a_cols,b_cols);
    multiply_ikj(A,B,C,a_rows,a_cols,b_cols);
    multiply_jik(A,B,C,a_rows,a_cols,b_cols);
    multiply_jki(A,B,C,a_rows,a_cols,b_cols);
    multiply_kij(A,B,C,a_rows,a_cols,b_cols);
    multiply_kji(A,B,C,a_rows,a_cols,b_cols);
    return;
}
