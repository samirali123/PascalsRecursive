// Samir Ali
// lab2.cpp
// CPSC2430
// Professor Diaz

// Purpose: To find a coefficient in Pascal's triangle with 2 different methods,
// recursively, and iteratively. We then compare the 2 execution times to see how efficient
// both methods are with different parameters.



#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;


// Desc: Creates the double array matrix to store pascal's triangle, using the
// provided degree from the commandline.
// Pre: degree int from commandline
// Post: int[][] matrix filled with Pascal's Triangle
int** createTriangle(int degree);


// Desc: Simply finds the coefficient using the degree and index
// Pre: int[][] matrix, int degree, and int index
// Post: int result, or the coefficient found within the matrix
int iterativeTriangle(int** M, int degree, int index);

// Desc: Method that recursively calls itself to find a coefficient of a
// certain index and degree
// Pre: int degree and int index, from the commandline
// Post: The coefficient from recursively calling itself
int recursiveTriangle(int degree, int index);

// Desc: Dynamically deallocates the memory for the int[][] matrix that was used to
// iteratively find the coefficient.
// Pre: int[][] matrix, int degree from the commandline
// Post: N/A
void deleteTriangle(int** M, int degree);

// Desc: Hosts the commandline values, print statements, and the timing.

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Usage: <degree> <index>" << endl;
        return 0; 
        
    }

    int degree = atoi(argv[1]); // degree of wanted coefficient
    int index = atoi(argv[2]); // how far into pascal's you want to go into

    auto start = high_resolution_clock::now(); // time placeholder

    int** pascals = createTriangle(degree); // matrix for iterative method
    int result = iterativeTriangle(pascals, degree, index); // coefficient from iterative method

    auto stop = high_resolution_clock::now(); // time placeholder

    auto duration = stop - start; // calculating displacement of time to find execution time
    auto duration_ns = duration_cast<nanoseconds>(duration); // changing time to nanoseconds

    cout << "Iterative approach result: " << result << endl;
    cout << "Iterative time: " << duration_ns.count() << "ns" << endl;
    deleteTriangle(pascals, degree);

    auto start2 = high_resolution_clock::now(); // time placeholder

    result = recursiveTriangle(degree, index); // result from recursively finding coefficient

    auto stop2 = high_resolution_clock::now(); // time placeholder

    auto duration2 = stop2 - start2; // finding displacement
    auto duration_ns2 = duration_cast<nanoseconds>(duration2); // changing to ns

    cout << "Recursive approach result: " << result << endl;
    cout << "Recutsive time: " << duration_ns2.count() << "ns" << endl;



    return 0;


}

int** createTriangle(int degree) {

    int** M = new int*[degree + 1]; // Creating matrix
    for (int i = 0; i < degree + 1; i++) {
        M[i] = new int[i + 1];
        M[i][0] = M[i][i] = 1;
        for (int j = 1; j < i; j++) {
            M[i][j] = M[i - 1][j - 1] + M[i - 1][j];
        }
    }

    return M;
}

int iterativeTriangle(int** M, int degree, int index) {
    return M[degree][index];
}

int recursiveTriangle(int degree, int index) {
    if (degree == 0 || index == 0 || degree == index) {
        return 1;
    }
    else {
        return recursiveTriangle(degree - 1, index - 1) + recursiveTriangle(degree - 1, index);
    }
}

void deleteTriangle(int** M, int degree) {
    for (int i = 0; i < degree; i++) {
        delete[] M[i];
    }
    delete[] M;
}

