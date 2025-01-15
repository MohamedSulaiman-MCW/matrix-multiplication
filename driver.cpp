#include <iostream>
#include <fstream>
#include "matmul.hpp"
using namespace std;

void addToCsv(int testCase,string status,string err,int* timeTaken);

//function to write the results into the csv file
void addToCsv(int testCase,string status,string err,int* timeTaken){
    ofstream writeCsv("./result.csv",ios::app);
    writeCsv << "Unit test case " << testCase << "," <<status <<","<< err<<",";
    for(int i=0;i<6;i++){
        writeCsv << timeTaken[i]<<",";
    }
    writeCsv << "\n";
    writeCsv.close();
}

int main(){ 
    int testNum=12;
    string testcases[testNum];

    //storing paths of each test cases in an array
    for(int i=0;i<testNum;i++){
        testcases[i]="./Unit_test/unit_" + std::to_string(i+1);
    }

    //writing the headings for results into csv file
    ofstream writeFile("./result.csv",ios::out);
    writeFile <<"Test Case,Status,ijk (ms),ikj (ms),jik (ms),jki (ms),kij (ms),kji (ms)\n";
    writeFile.close();

    //iterating over all the unit test cases
    string err;
    int timeTaken[6];
    for(int i=0;i<testNum;i++){

        //initializing the time taken for every iteration as 0
        for(int i=0;i<6;i++){
            timeTaken[i]=0;
        }

        cout << "Running Unit test case "<<i+1<<"\n\n";
        int row1;
        int col1;
        string filenameA=testcases[i]+"/A.txt";
        ifstream readFileA(filenameA);
        readFileA >> row1 >> col1;
        double **A = new double*[row1];
        for (int i = 0; i < row1; i++) {
            A[i] = new double[col1];
        }

        //reading matrix input from test case
        int flag=0;//flag for finding invalid character
        for(int i=0;i<row1;i++){
            for(int j=0;j<col1;j++){
                readFileA >> A[i][j];
                if (readFileA.fail()) {
                    cout << "Not a valid integer at position (" << i << ", " << j << ")\n" << endl;
                    flag = 1;
                    break;
                }
            }
        }
        if(flag==1){
            err="Invalid character found ";
            addToCsv(i+1,"Failed",err,timeTaken);
            continue;
        }
        // printArray(A,row1,col1);
        int row2,col2;
        string filenameB=testcases[i]+"/B.txt";
        ifstream readFileB(filenameB);
        readFileB >> row2 >> col2;

        //checking dimension mismatch
        if(col1!=row2){
            err="Dimension Mismatch";
            cout << "Dimension Mismatch \n\n";
            addToCsv(i+1,"Failed",err,timeTaken);
            continue;
        }

        double **B = new double*[row2];
        for (int i = 0; i < row2; i++) {
            B[i] = new double[col2];
        }

        
        //reading matrix input from test case
        flag=0;
        for(int i=0;i<row2;i++){
            for(int j=0;j<col2;j++){
                readFileB >> B[i][j];
                if (readFileB.fail()) {
                    cout << "Not a valid integer at position (" << i << ", " << j << ")\n" << endl;
                    flag = 1;
                    break;
                }
            }
        }
        if(flag==1){
            err="Invalid character found ";
            addToCsv(i+1,"Failed",err,timeTaken);
            continue;
        }

        int row3,col3;
        string filenameC=testcases[i]+"/C.txt";
        ifstream readFileC(filenameC);
        readFileC >> row3 >> col3;
        double **C = new double*[row3];
        for (int i = 0; i < row3; i++) {
            C[i] = new double[col3];
        }
        for(int i=0;i<row3;i++){
            for(int j=0;j<col3;j++){
                readFileC >> C[i][j];
            }
        }

        //declaring a 2d array to store the result
        double **result = new double*[row1];
        for (int i = 0; i < row1; i++) {
            result[i] = new double[col2];
        }

        //passing arguments to the multiplication function
        matrix_multiplication(A,B,result,row1,col1,col2,timeTaken);

        cout << "\n";
        cout << "Result: ";

        //comparing the result
        if(compare(C,result,row3,col3)==0){
            err="Wrong answer ";
            addToCsv(i+1,"Failed",err,timeTaken);
            cout <<"Failed \n";
        }
        else{
            err="Success";
            addToCsv(i+1,"Passed",err,timeTaken);
            cout <<"Passed \n";
        }
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
