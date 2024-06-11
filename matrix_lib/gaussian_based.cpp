#include "gaussian_based.h"

namespace matrix_lib {
    void apply_inplace(Matrix &mat, const gaussian_elimination::Operations &ops) {
        for (const auto &op: ops) {
            op->apply(mat);
        }
    }

    Matrix apply(const Matrix &mat, const gaussian_elimination::Operations &ops) {
        auto copy = mat;
        apply_inplace(copy, ops);
        return copy;
    }

    double det_from_canonical(const Matrix &canonical_form, const gaussian_elimination::Operations &ops) {
        bool is_eye = true;
        for (size_t i = 0; i < canonical_form.rows(); ++i) {
            if (canonical_form[i][i] != 1) {
                is_eye = false;
                break;
            }
        }

        if (!is_eye) {
            return 0;
        }

        double res = 1;
        for (const auto &op: ops) {
            res *= op->det_coefficient();
        }
        return res;
    }

    double det(const Matrix &matrix) {
        auto copy = matrix;
        auto &&ops = gaussian_elimination::eliminate_inplace(copy);
        return det_from_canonical(copy, ops);
    }

    size_t rank_from_canonical_form(const Matrix &canonical_form) {
        for (size_t i = canonical_form.rows(); i > 0; --i) {
            size_t row = i - 1;
            for (auto j: canonical_form[row]) {
                if (j != 0) {
                    return i;
                }
            }
        }
        return 0;
    }

    size_t rank(const Matrix &mat) {
        auto copy = mat;
        gaussian_elimination::eliminate_inplace(copy);
        return rank_from_canonical_form(copy);
    }

    Matrix nullspace_from_canonical_form(const Matrix &canonical_form, size_t rank) {
        std::vector<std::vector<double>> res(canonical_form.columns(),
                                             std::vector<double>(canonical_form.columns() - rank, 0));
        std::vector<size_t> dependent_variables{};
        dependent_variables.reserve(rank);

        size_t d = 0;

        for (size_t i = 0; i < canonical_form.columns(); ++i) {
            if (i - d < canonical_form.rows() && canonical_form[i - d][i] != 0) {
                dependent_variables.push_back(i);
                continue;
            }
            ++d;

            for (size_t j = 0; j < d; ++j) {
                res[dependent_variables[j]][d - 1] = -canonical_form[j][i];
            }
            res[i][d - 1] = 1;
        }

        return Matrix(res);
    }

    Matrix nullspace_from_canonical_form(const Matrix &canonical_form) {
        size_t rank = rank_from_canonical_form(canonical_form);
        return nullspace_from_canonical_form(canonical_form, rank);
    }

    Matrix nullspace(const Matrix &matrix) {
        auto copy = matrix;
        gaussian_elimination::eliminate_inplace(copy);
        return nullspace_from_canonical_form(copy);
    }

    Matrix inverse_from_operations(size_t n, const gaussian_elimination::Operations &ops) {
        auto res = Matrix::identity(n);
        apply_inplace(res, ops);
        return res;
    }

    Matrix inverse(const Matrix &mat) {
        gaussian_elimination::Operations ops = gaussian_elimination::eliminate(mat);
        return inverse_from_operations(mat.rows(), ops);
    }
}

