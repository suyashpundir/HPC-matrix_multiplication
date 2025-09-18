#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// Function to generate a matrix filled with random numbers
vector<vector<double>> generate_matrix(int n) {
    vector<vector<double>> mat(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = rand() % 10;  // random values [0–9]
        }
    }
    return mat;
}

// Sequential matrix multiplication
vector<vector<double>> multiply(const vector<vector<double>>& A,
                                const vector<vector<double>>& B,
                                int n) {
    vector<vector<double>> C(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

int main() {
    srand(time(0));
    vector<int> sizes = {256, 512}; // matrix sizes to test

    for (int n : sizes) {
        auto A = generate_matrix(n);
        auto B = generate_matrix(n);

        auto start = chrono::high_resolution_clock::now();
        auto C = multiply(A, B, n);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;
        cout << "Matrix Size " << n << "x" << n
             << " : Time = " << duration.count() << " seconds" << endl;
    }
    return 0;
}
