#ifndef MATRIX_LIB_MATRIX_H
#define MATRIX_LIB_MATRIX_H

#include <vector>

class Matrix {
private:
    std::vector<std::vector<double>> inner;
public:
    explicit Matrix(const std::vector<std::vector<double>> &mat);

    explicit Matrix(std::vector<std::vector<double>> &&mat);

    Matrix &operator=(const std::vector<std::vector<double>> &mat);

    Matrix &operator=(std::vector<std::vector<double>> &&mat);

    Matrix(const Matrix &other);

    Matrix(Matrix &&other) noexcept;

    Matrix &operator=(const Matrix &other);

    Matrix &operator=(Matrix &&other) noexcept;

    std::vector<double> &operator[](size_t x);

    const std::vector<double> &operator[](size_t x) const;

    [[nodiscard]] size_t rows() const;

    [[nodiscard]] size_t columns() const;

    Matrix &operator+=(const Matrix &other);

    Matrix &operator-=(const Matrix &other);

    Matrix &operator*=(double scalar);

    Matrix &operator/=(double scalar);

    friend void transpose_inplace(Matrix &mat);

    static Matrix identity(size_t n);
};

Matrix transpose(const Matrix &mat);

Matrix operator+(const Matrix &mat);

Matrix operator-(const Matrix &mat);

Matrix operator+(const Matrix &lhs, const Matrix &rhs);

Matrix operator-(const Matrix &lhs, const Matrix &rhs);

Matrix operator*(const Matrix &lhs, double rhs);

Matrix operator*(double lhs, const Matrix &rhs);

Matrix operator*(const Matrix &lhs, const Matrix &rhs);

Matrix operator/(const Matrix &lhs, double rhs);


#endif //MATRIX_LIB_MATRIX_H
