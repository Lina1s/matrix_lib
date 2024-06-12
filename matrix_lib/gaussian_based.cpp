///@cond
#include "gaussian_based.h"
#include "exceptions.h"
///@endcond
namespace matrix_lib {
    ///@cond
    bool is_eye(const Matrix &mat) {
        if (mat.rows() != mat.columns()) {
            return false;
        }
        for (size_t i = 0; i < mat.rows(); ++i) {
            if (mat[i][i] != 1) {
                return false;
            }
        }
        return true;
    }
    ///@endcond


    /// @headerfile gaussian_based.h
    void apply_inplace(Matrix &mat, const gaussian_elimination::Operations &ops) {
        for (const auto &op: ops) {
            op->apply(mat);
        }
    }

    /// @headerfile gaussian_based.h
    Matrix apply(const Matrix &mat, const gaussian_elimination::Operations &ops) {
        auto copy = mat;
        apply_inplace(copy, ops);
        return copy;
    }

    /// @headerfile gaussian_based.h
    double det_from_canonical(const Matrix &canonical_form, const gaussian_elimination::Operations &ops) {
        if (!is_eye(canonical_form)) {
            return 0;
        }

        double res = 1;
        for (const auto &op: ops) {
            res *= op->det_coefficient();
        }
        return res;
    }

    /// @headerfile gaussian_based.h
    double det(const Matrix &matrix) {
        if (matrix.columns() != matrix.rows()) {
            throw ShapeError("Attempt to evaluate det of non-square matrix");
        }
        auto copy = matrix;
        auto &&ops = gaussian_elimination::eliminate_inplace(copy);
        return det_from_canonical(copy, ops);
    }

    /// @headerfile gaussian_based.h
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

    /// @headerfile gaussian_based.h
    size_t rank(const Matrix &mat) {
        auto copy = mat;
        gaussian_elimination::eliminate_inplace(copy);
        return rank_from_canonical_form(copy);
    }

    /// @headerfile gaussian_based.h
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

            for (size_t j = 0; j < dependent_variables.size(); ++j) {
                res[dependent_variables[j]][d - 1] = -canonical_form[j][i];
            }
            res[i][d - 1] = 1;
        }

        return Matrix(res);
    }

    /// @headerfile gaussian_based.h
    Matrix nullspace_from_canonical_form(const Matrix &canonical_form) {
        size_t rank = rank_from_canonical_form(canonical_form);
        return nullspace_from_canonical_form(canonical_form, rank);
    }

    /// @headerfile gaussian_based.h
    Matrix nullspace(const Matrix &matrix) {
        auto copy = matrix;
        gaussian_elimination::eliminate_inplace(copy);
        return nullspace_from_canonical_form(copy);
    }

    /// @headerfile gaussian_based.h
    Matrix inverse_from_operations(size_t n, const gaussian_elimination::Operations &ops) {
        auto res = Matrix::identity(n);
        apply_inplace(res, ops);
        return res;
    }

    /// @headerfile gaussian_based.h
    Matrix inverse(const Matrix &mat) {
        auto copy = mat;
        gaussian_elimination::Operations ops = gaussian_elimination::eliminate_inplace(copy);
        if (!is_eye(copy)) {
            throw InvalidOperationError("Attempt to inverse singular or non-square matrix");
        }
        return inverse_from_operations(mat.rows(), ops);
    }
}

///@file
