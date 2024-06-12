///@cond
#include "operations.h"

#include <cmath>
///@endcond
namespace matrix_lib::gaussian_elimination {
    /// @headerfile operations.h
    Operation::~Operation() = default;

    std::wostream &operator<<(std::wostream &os, const Operation &op) {
    /// @headerfile operations.h
    std::ostream &operator<<(std::ostream &os, const Operation &op) {
        op.print(os);
        return os;
    }

    /// @headerfile operations.h
    Normalize::Normalize(size_t row, double scalar) : row(row), scalar(scalar) {

    }

    /// @headerfile operations.h
    void Normalize::apply(Matrix &matrix) const {
        for (auto &el: matrix[row]) {
            el /= scalar;
        }
    }

    /// @headerfile operations.h
    double Normalize::det_coefficient() const {
        return scalar;
    }

    void Normalize::print(std::wostream &os) const {
        os << L'(' << row << L") /= " << scalar;
    /// @headerfile operations.h
    void Normalize::print(std::ostream &os) const {
        os << '(' << row << ") /= " << scalar;
    }

    /// @headerfile operations.h
    Swap::Swap(size_t row1, size_t row2) : row1(row1), row2(row2) {

    }

    /// @headerfile operations.h
    void Swap::apply(Matrix &matrix) const {
        std::swap(matrix[row1], matrix[row2]);
    }

    /// @headerfile operations.h
    double Swap::det_coefficient() const {
        return row1 - row2 == 0 ? 1 : -1;
    }

    /// @headerfile operations.h
    void Swap::print(std::ostream &os) const {
        os << '(' << row1 << ") <-> (" << row2 << ')';
    void Swap::print(std::wostream &os) const {
        os << L'(' << row1 << L") <-> (" << row2 << L')';
    }

    /// @headerfile operations.h
    Subtract::Subtract(size_t rowSource, size_t rowTarget, double scalar) : row_source(rowSource),
                                                                            row_target(rowTarget),
                                                                            scalar(scalar) {}

    /// @headerfile operations.h
    void Subtract::apply(Matrix &matrix) const {
        for (size_t i = 0; i < matrix.columns(); ++i) {
            matrix[row_target][i] -= scalar * matrix[row_source][i];
        }
    }

    /// @headerfile operations.h
    double Subtract::det_coefficient() const {
        return 1;
    }

    /// @headerfile operations.h
    void Subtract::print(std::ostream &os) const {
        os << '(' << row_target << ") -= " << scalar << " * (" << row_source << ')';
    void Subtract::print(std::wostream &os) const {
        os << L'(' << row_target << L") -= " << scalar << L" * (" << row_source << L')';
    }
}
///@file
