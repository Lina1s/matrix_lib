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


