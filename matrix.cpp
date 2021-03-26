#include <iostream>
#include <cmath>
#include "matrix.hpp"

Matrix::Matrix() :
    name{0},
    numOfRows{0},
    numOfColumns{0},
    value{nullptr}
{}

Matrix::Matrix(char name, int numOfRows, int numOfColumns, double **newValue) :
    name{name},
    numOfRows{numOfRows},
    numOfColumns{numOfColumns},
    value{new double[numOfRows * numOfColumns]}
{
    for(int i = 0; i < numOfRows; i++) {
        for(int j = 0; j < numOfColumns; j++)
            value[numOfColumns * i + j] = newValue[i][j];
    }
}

Matrix::Matrix(Matrix const &source) :
    name{source.name},
    numOfRows{source.numOfRows},
    numOfColumns{source.numOfColumns},
    value{new double[numOfRows * numOfColumns]}
{
    for(int i = 0; i < numOfRows; i++) {
        for(int j = 0; j < numOfColumns; j++)
            value[numOfColumns * i + j] = source.value[numOfColumns * i + j];
    }
}

Matrix::~Matrix() {
    delete [] value;
}

auto Matrix::operator=(Matrix const &source) -> Matrix & {
    name = source.name;
    numOfRows = source.numOfRows;
    numOfColumns = source.numOfColumns;

    delete [] value;
    value = new double[numOfRows * numOfColumns];

    for(int i = 0; i < numOfRows; i++) {
        for(int j = 0; j < numOfColumns; j++)
            value[numOfColumns * i + j] = source.getValue(i, j);
    }

    return *this;
}

auto Matrix::operator*(double coefficient) const -> Matrix {
    auto matrix = Matrix(*this);
    for(int i = 0; i < matrix.numOfRows; i++) {
        for(int j = 0; j < matrix.numOfColumns; j++) {
            matrix.value[matrix.numOfColumns * i + j] *= coefficient;
        }
    }
    return matrix;
}

auto Matrix::operator*(Matrix const &second) const -> Matrix {
    if(numOfColumns != second.numOfRows) {
        std::cout << "Error!\n";
        auto result = Matrix();
        result.setName('0');
        return result;
    } else {
        auto **array = new double *[numOfRows];
        for (int i = 0; i < numOfRows; i++) {
            array[i] = new double[second.numOfColumns];
            for (int j = 0; j < second.numOfColumns; j++) {
                array[i][j] = 0;
                for (int s = 0; s < numOfColumns; s++)
                    array[i][j] += getValue(i, s) * second.getValue(s, j);
            }
        }
        auto product = Matrix(fmax(name, second.name) + 1, numOfRows, second.numOfColumns, array);
        return product;
    }
}

auto Matrix::operator~() const -> Matrix {
    auto **array = new double*[numOfColumns];
    for(int i = 0; i < numOfColumns; i++) {
        array[i] = new double[numOfRows];
        for(int j = 0; j < numOfRows; j++)
            array[i][j] = getValue(j, i);
    }
    auto transpose = Matrix(name, numOfColumns, numOfRows, array);
    return transpose;
}

auto Matrix::operator--() -> Matrix & {
    for(int i = 0; i < numOfRows; i++) {
        for(int j = 0; j < numOfColumns; j++)
            value[numOfColumns * i + j]--;
    }
    return *this;
}

auto operator<<(std::ostream &os, Matrix const &matrix) -> std::ostream & {
    os << "Matrix " << matrix.name << ":\n";
    for(int i = 0; i < matrix.numOfRows; i++) {
        std::cout << "\t";
        for(int j = 0; j < matrix.numOfColumns; j++)
            std::cout << matrix.value[matrix.numOfColumns * i + j] << "\t";
        std::cout << "\n";
    }
    std::cout << "\n";
    return os;
}

auto Matrix::getValue(int i, int j) const -> double {
    return value[numOfColumns * i + j];
}

auto Matrix::setName(char newName) -> void {
    name = newName;
}

auto Matrix::increaseName() -> void {
    name++;
}

auto Matrix::getModified(double (*func)(double)) -> Matrix & {
    if(func != nullptr) {
        for(int i = 0; i < numOfRows; i++) {
            for(int j = 0; j < numOfColumns; j++)
                value[numOfColumns * i + j] = func(value[numOfColumns * i + j]);
        }
    }
    return *this;
}