#include "Matrix.h"

Matrix::Matrix(const std::vector<std::vector<double>> &mat): inner(mat) {
}

Matrix::Matrix(std::vector<std::vector<double>> &&mat): inner(std::move(mat)) {
}

Matrix &Matrix::operator=(const std::vector<std::vector<double>> &mat) {
    inner = mat;
    return *this;
}

Matrix &Matrix::operator=(std::vector<std::vector<double>> &&mat) {
    inner = std::move(mat);
    return *this;

}

Matrix::Matrix(const Matrix &other) {
    inner = other.inner;
}

Matrix::Matrix(Matrix &&other) noexcept {
    inner = std::move(other.inner);
}

Matrix &Matrix::operator=(const Matrix &other) = default;

Matrix &Matrix::operator=(Matrix &&other)  noexcept {
    inner = std::move(other.inner);
    return *this;
}

std::vector<double> &Matrix::operator[](int x) {
    return inner[x];
}

const std::vector<double> &Matrix::operator[](int x) const {
    return inner[x];
}

size_t Matrix::rows() const{
    return inner.size();
}

size_t Matrix::columns() const {
    if (rows() == 0) {
        return 0;
    } return inner[0].size();
}

Matrix &Matrix::operator+=(const Matrix &other) {
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < columns(); ++j) {
            inner[i][j] += other.inner[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < columns(); ++j) {
            inner[i][j] -= other.inner[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(double scalar) {
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < columns(); ++j) {
            inner[i][j] *= scalar;
        }
    }
    return *this;
}

Matrix &Matrix::operator/=(double scalar) {
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < columns(); ++j) {
            inner[i][j] /= scalar;
        }
    }
    return *this;
}


Matrix operator+(const Matrix &mat) {
    auto res = mat;
    return res;
}

Matrix operator-(const Matrix &mat) {
    auto res = mat;
    res *= -1;
    return res;
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
    auto res = lhs;
    res += rhs;
    return res;
}

Matrix operator-(const Matrix &lhs, const Matrix &rhs) {
    auto res = lhs;
    res -= rhs;
    return res;
}

Matrix operator*(const Matrix &lhs, double rhs) {
    auto res = lhs;
    res *= rhs;
    return res;
}

Matrix operator*(double lhs, const Matrix &rhs) {
    auto res = rhs;
    res *= lhs;
    return res;
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
    std::vector<std::vector<double>> res(lhs.rows(), std::vector<double>(rhs.columns(), 0));
    for (int row = 0; row < lhs.rows(); ++row) {
        for (int column = 0; column < rhs.columns(); ++column) {
            for (int k = 0; k < lhs.columns(); ++k) {
                res[row][column] += lhs[row][k] * rhs[k][column];
            }
        }
    }
    return res;
}

Matrix operator/(const Matrix &lhs, double rhs) {
    auto res = lhs;
    res /= rhs;
    return res;
}
