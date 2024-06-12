#include "Matrix.h"
#include "exceptions.h"

namespace matrix_lib {
    bool Matrix::is_matrix(const std::vector<std::vector<double>> &mat) {
        if (mat.empty()) {
            return true;
        }
        size_t m = mat[0].size();
        for (size_t i = 1; i < mat.size(); ++i) {
            if (mat[i].size() != m) {
                return false;
            }
        }
        return true;
    }

    Matrix::Matrix(const std::vector<std::vector<double>> &mat) : inner(mat) {
        if (!is_matrix(mat)) {
            throw VectorError("Rows of vector have different sizes");
        }
    }

    Matrix::Matrix(std::vector<std::vector<double>> &&mat) : inner(std::move(mat)) {
        if (!is_matrix(mat)) {
            throw VectorError("Rows of vector have different sizes");
        }
    }

    Matrix &Matrix::operator=(const std::vector<std::vector<double>> &mat) {
        if (!is_matrix(mat)) {
            throw VectorError("Rows of vector have different sizes");
        }
        inner = mat;
        return *this;
    }

    Matrix &Matrix::operator=(std::vector<std::vector<double>> &&mat) {
        if (!is_matrix(mat)) {
            throw VectorError("Rows of vector have different sizes");
        }
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

    Matrix &Matrix::operator=(Matrix &&other) noexcept {
        inner = std::move(other.inner);
        return *this;
    }

    std::vector<double> &Matrix::operator[](size_t x) {
        return inner.at(x);
    }

    const std::vector<double> &Matrix::operator[](size_t x) const {
        return inner.at(x);
    }

    size_t Matrix::rows() const {
        return inner.size();
    }

    size_t Matrix::columns() const {
        if (rows() == 0) {
            return 0;
        }
        return inner[0].size();
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
        if (scalar == 0) {
            throw std::overflow_error("Attempt to divide by 0");
        }
        for (size_t i = 0; i < rows(); ++i) {
            for (size_t j = 0; j < columns(); ++j) {
                inner[i][j] /= scalar;
            }
        }
        return *this;
    }

    void transpose_inplace(Matrix &mat) {
        size_t min_dim = std::min(mat.rows(), mat.columns());
        for (size_t i = 0; i < min_dim; ++i) {
            for (size_t j = i + 1; j < min_dim; ++j) {
                std::swap(mat[i][j], mat[j][i]);
            }
        }

        if (mat.rows() < mat.columns()) {
            size_t rows = mat.rows();
            size_t columns = mat.columns();
            for (size_t i = 0; i < columns - rows; ++i) {
                mat.inner.emplace_back(rows);
            }

            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = rows; j < columns; ++j) {
                    std::swap(mat[i][j], mat[j][i]);
                }
                mat[i].resize(rows);
            }
        } else if (mat.rows() > mat.columns()) {
            size_t rows = mat.rows();
            size_t columns = mat.columns();

            for (size_t i = 0; i < columns; ++i) {
                mat[i].resize(rows);
            }

            for (size_t i = 0; i < columns; ++i) {
                for (size_t j = columns; j < rows; ++j) {
                    std::swap(mat[i][j], mat[j][i]);
                }
            }
            mat.inner.resize(columns);
        }
    }

    Matrix Matrix::identity(size_t n) {
        std::vector<std::vector<double>> res(n, std::vector<double>(n, 0));
        for (int i = 0; i < n; ++i) {
            res[i][i] = 1;
        }
        return Matrix(res);
    }

    Matrix::Matrix(std::initializer_list<std::vector<double>> rows) : Matrix(std::vector(rows)) {
    }


    Matrix transpose(const Matrix &mat) {
        auto copy = mat;
        transpose_inplace(copy);
        return copy;
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
        return Matrix(res);
    }

    Matrix operator/(const Matrix &lhs, double rhs) {
        auto res = lhs;
        res /= rhs;
        return res;
    }
}
