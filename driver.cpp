#include <iostream>
#include <fstream>
#include "matmul.hpp"
#include <sstream>
using namespace std;

void addToCsv(int testCase,string status,string err,int* timeTaken);
void runTestCase(int* timeTaken,string directory,int testNum);

//function to find the data type of the input
string detectDataType(const string& filePath) {
    ifstream file(filePath);
    string value;
    int count=0;
    while(file >> value){
        count++;
        if(count==3){
            break;
        }
    }

    // Check if the value contains a decimal point
    if (value.find('.') != std::string::npos) {
        return "double";  // Contains a decimal, so it's a double
    } else {
        return "int";     // No decimal, so it's an integer
    }
}

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

//template function to read the inputs and call the matrix multiplication function
template <typename T>
void runTestCase(int* timeTaken,string directory,int testNum){
    cout << "Running Unit test case "<<testNum<<"\n\n";
    string err;
    int row1;
    int col1;
    string filenameA=directory+"/A.txt";
    ifstream readFileA(filenameA);
    readFileA >> row1 >> col1;
    T **A = new T*[row1];
    for (int i = 0; i < row1; i++) {
        A[i] = new T[col1];
    }

    //reading matrix1 input from test case
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
        addToCsv(testNum,"Failed",err,timeTaken);
        return;
    }

    int row2,col2;
    string filenameB=directory+"/B.txt";
    ifstream readFileB(filenameB);
    readFileB >> row2 >> col2;

    //checking dimension mismatch
    if(col1!=row2){
        err="Dimension Mismatch";
        cout << "Dimension Mismatch \n\n";
        addToCsv(testNum,"Failed",err,timeTaken);
        return;
    }

    T **B = new T*[row2];
    for (int i = 0; i < row2; i++) {
        B[i] = new T[col2];
    }

    //reading matrix2 input from test case
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
        addToCsv(testNum,"Failed",err,timeTaken);
        return;
    }

    //reading resultant matrix
    int row3,col3;
    string filenameC=directory+"/C.txt";
    ifstream readFileC(filenameC);
    readFileC >> row3 >> col3;
    T **C = new T*[row3];
    for (int i = 0; i < row3; i++) {
        C[i] = new T[col3];
    }
    for(int i=0;i<row3;i++){
        for(int j=0;j<col3;j++){
            readFileC >> C[i][j];
        }
    }

    //declaring a 2d array to store the result
    T **result = new T*[row1];
    for (int i = 0; i < row1; i++) {
        result[i] = new T[col2];
    }

    //passing arguments to the multiplication function
    matrix_multiplication(A,B,result,row1,col1,col2,timeTaken);

    cout << "\n";
    cout << "Result: ";

    //comparing the result
    if(compare(C,result,row3,col3)==0){
        err="Wrong answer ";
        addToCsv(testNum,"Failed",err,timeTaken);
        cout <<"Failed \n";
    }
    else{
        err="Success";
        addToCsv(testNum,"Passed",err,timeTaken);
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

int main(){ 
    int testNum=14;
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
    int timeTaken[6];
    for(int i=0;i<testNum;i++){

        //initializing the time taken for every iteration as 0
        for(int i=0;i<6;i++){
            timeTaken[i]=0;
        }
        string value;
        int count=0;
        ifstream readDatatype(testcases[i]+"/A.txt");
        if (detectDataType(testcases[i] + "/A.txt") == "double") {
            runTestCase<double>(timeTaken,testcases[i], i + 1);
        } else {
            runTestCase<int>(timeTaken,testcases[i], i + 1);
        }
    }
    return 0;
}
