#include <iostream>
#include <cmath>
#include "matrix.hpp"

int main() {
    int numOfRows = 2;
    int numOfColumns = 3;

    auto **array = new double*[numOfRows];
    for(int i = 0; i < numOfRows; i++) {
        array[i] = new double[numOfColumns];
        for(int j = 0; j < numOfColumns; j++)
            array[i][j] = 1 + i + j;
    }

    std::cout << "Array:\n";
    for(int i = 0; i < numOfRows; i++) {
        for(int j = 0; j < numOfColumns; j++)
            std::cout << array[i][j] << " ";
        std::cout << "\n";
    }

    auto matrix1 = Matrix('A', numOfRows, numOfColumns, array);
    std::cout << matrix1;

    auto matrix2 = matrix1 * 2;
    --matrix2;
    matrix2.increaseName();
    std::cout << matrix2;

    matrix2 = ~matrix2;
    std::cout << "Transpose Matrix B:\n";
    std::cout << matrix2;

    std::cout << "C = A * B\n";
    auto matrix3 = matrix1 * matrix2;
    std::cout << matrix3;

    std::cout << "Modified Matrix C by sqrt():\n";
    std::cout << matrix3.getModified(sqrt);

    return 0;
}
