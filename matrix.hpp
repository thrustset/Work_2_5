#pragma once
#include <iostream>

class Matrix {
private:
    char name;
    int numOfRows;
    int numOfColumns;
    double *value;
public:
    Matrix();
    Matrix(char name, int numOfRows, int numOfColumns, double **value);
    Matrix(Matrix const &source);
    ~Matrix();

    auto operator=(Matrix const &source) -> Matrix &;
    auto operator*(double coefficient) const -> Matrix;
    auto operator*(Matrix const &second) const -> Matrix;
    auto operator~() const -> Matrix;
    auto operator--() -> Matrix &;

    friend auto operator<<(std::ostream &os, Matrix const &matrix)  -> std::ostream &;

    auto getValue(int i, int j) const -> double;
    auto setName(char newName) -> void;
    auto increaseName() -> void;

    auto getModified(double (*func)(double) = nullptr) -> Matrix &;
};