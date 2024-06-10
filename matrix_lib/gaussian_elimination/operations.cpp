#include "operations.h"

#include <cmath>

namespace gaussian_elimination {
    GEOperation::~GEOperation() = default;

    std::ostream &operator<<(std::ostream &os, const GEOperation &op) {
        op.print(os);
        return os;
    }

    Normalize::Normalize(int row, double scalar) : row(row), scalar(scalar) {

    }

    void Normalize::apply(Matrix &matrix) const {
        for (auto &el: matrix[row]) {
            el /= scalar;
        }
    }

    double Normalize::det_coefficient() const {
        return scalar;
    }

    void Normalize::print(std::ostream &os) const {
        os << '(' << row << ") /= " << scalar;
    }

    Swap::Swap(int row1, int row2) : row1(row1), row2(row2) {

    }

    void Swap::apply(Matrix &matrix) const {
        std::swap(matrix[row1], matrix[row2]);
    }

    double Swap::det_coefficient() const {
        return row1 - row2 == 0 ? 1 : -1;
    }

    void Swap::print(std::ostream &os) const {
        os << '(' << row1 << ") <-> (" << row2 << ')';
    }

    Subtract::Subtract(int rowSource, int rowTarget, double scalar) : row_source(rowSource), row_target(rowTarget),
                                                                      scalar(scalar) {}

    void Subtract::apply(Matrix &matrix) const {
        for (size_t i = 0; i < matrix.columns(); ++i) {
            matrix[row_target][i] -= scalar * matrix[row_source][i];
        }
    }

    double Subtract::det_coefficient() const {
        return 1;
    }

    void Subtract::print(std::ostream &os) const {
        os << '(' << row_target << ") -= " << scalar << " * (" << row_source << ')';
    }
}