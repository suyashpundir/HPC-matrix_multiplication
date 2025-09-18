#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h>

using namespace std;

// Function to generate random matrix
vector<vector<double>> generate_matrix(int n) {
    vector<vector<double>> mat(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = rand() % 10;
        }
    }
    return mat;
}

// Parallel matrix multiplication using OpenMP
vector<vector<double>> multiply(const vector<vector<double>>& A,
                                const vector<vector<double>>& B,
                                int n, int num_threads) {
    vector<vector<double>> C(n, vector<double>(n, 0.0));

    omp_set_num_threads(num_threads);

    #pragma omp parallel for collapse(2)  // collapse merges i,j loops for better load balance
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    return C;
}

int main() {
    srand(time(0));
    vector<int> sizes = {256, 512};   // You can expand to 1024, 2048 later
    vector<int> threads = {1, 2, 4, 8};

    for (int n : sizes) {
        auto A = generate_matrix(n);
        auto B = generate_matrix(n);

        for (int t : threads) {
            auto start = chrono::high_resolution_clock::now();
            auto C = multiply(A, B, n, t);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double> duration = end - start;
            cout << "Matrix Size " << n << "x" << n
                 << " | Threads: " << t
                 << " | Time = " << duration.count() << " seconds" << endl;
        }
    }
    return 0;
}
