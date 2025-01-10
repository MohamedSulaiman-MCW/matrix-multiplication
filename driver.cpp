#include <iostream>
#include <fstream>
#include "matmul.hpp"
using namespace std;
void compare(int **result,int** C,int rows,int cols);
void compare(int** result,int ** C,int rows,int cols){
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(result[i][j]!=C[i][j]){
                cout << "Failed";
                break;
            }
        }
    }
    cout << "Passed";
}
int main(){
    int testNum=3;
    string testcases[testNum];

    //storing paths of each test cases
    for(int i=0;i<testNum;i++){
        testcases[i]="./Unit_test/unit_" + std::to_string(i+1);
    }

    //iterating over all the unit test cases
    for(int i=0;i<testNum;i++){
        // cout << "inside";
        int row;
        int col;
        string filenameA=testcases[i]+"/A.txt";
        ifstream readFileA(filenameA);
        readFileA >> row >> col;
        int **A = new int*[row];
        for (int i = 0; i < row; i++) {
            A[i] = new int[col];
        }

        //reading matrix input from test case
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                readFileA >> A[i][j];
            }
        }

        // cout << filenameA;
        //printing the martrix A
        // for (int i = 0; i < row; i++) {
        //     for (int j = 0; j < col; j++) {
        //         cout << A[i][j] << " ";
        //     }
        //     cout << endl;
        // }

        string filenameB=testcases[i]+"/B.txt";
        ifstream readFileB(filenameB);
        readFileB >> row >> col;
        int **B = new int*[row];
        for (int i = 0; i < row; i++) {
            B[i] = new int[col];
        }

        //reading matrix input from test case
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                readFileB >> B[i][j];
            }
        }

        //printing the matrix B
        // for (int i = 0; i < row; i++) {
        //     for (int j = 0; j < col; j++) {
        //         cout << B[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        string filenameC=testcases[i]+"/C.txt";
        ifstream readFileC(filenameC);
        readFileC >> row >> col;
        int **C = new int*[row];
        for (int i = 0; i < row; i++) {
            C[i] = new int[col];
        }
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                readFileC >> C[i][j];
            }
        }
        //declaring a 2d array to store the result
        int **result = new int*[row];
        for (int i = 0; i < row; i++) {
            result[i] = new int[col];
        }

        //passing arguments to the multiplication function
        matrix_multiplication(A,B,result,row,col,col);

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << result[i][j] << " ";
            }
            cout << endl;
        }
        cout << "\n";
        cout << "Result: ";
        compare(C,result,row,col);
        cout << "\n \n";

        for (int i = 0; i < 2; i++) {
            delete[] A[i];
            delete[] B[i];
            delete[] C[i];
        }
        delete[] A;
        delete[] B;
        delete[] C;
    }
    return 0;
}