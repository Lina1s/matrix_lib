#ifndef MATRIX_LIB_MATRIX_H
#define MATRIX_LIB_MATRIX_H

#include <vector>

class Matrix {
private:
    std::vector<std::vector<double>> inner;
public:
    Matrix(const std::vector<std::vector<double>> &mat);
    Matrix(std::vector<std::vector<double>> &&mat);
    Matrix &operator=(const std::vector<std::vector<double>> &mat);
    Matrix &operator=(std::vector<std::vector<double>> &&mat);

    Matrix(const Matrix &other);
    Matrix(Matrix &&other) noexcept ;
    Matrix &operator=(const Matrix &other);
    Matrix &operator=(Matrix &&other) noexcept;

    std::vector<double> &operator[](int x);
};


#endif //MATRIX_LIB_MATRIX_H
