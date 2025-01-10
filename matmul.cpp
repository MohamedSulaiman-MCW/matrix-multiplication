#include<iostream>

using namespace std;
void matrix_multiplication(int **A , int **B , int **C ,int a_rows,int a_cols,int b_cols){
    // cout << "inside the function";
    for(int i=0;i<a_rows;i++){
        for(int j=0;j<b_cols;j++){
            C[i][j]=0;
            for(int k=0;k<a_cols;k++){
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
    return;
}