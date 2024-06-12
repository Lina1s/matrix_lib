///@cond
#include "elimination.h"
///@endcond

static double rnd(double val) {
    static double prec = 1e-7;
    if (std::abs(val) < prec) {
        return 0;
    }
    return val;
}

namespace matrix_lib::gaussian_elimination {
    /// @headerfile elimination.h
    std::vector<std::unique_ptr<Operation>> eliminate_inplace(Matrix &mat) {

        std::vector<std::unique_ptr<Operation>> res{};
        size_t d = 0;
        for (size_t i = 0; i < mat.columns(); ++i) {
            bool subtract = true;
            size_t row = i - d;
            if (row >= mat.rows()) {
                break;
            }
            if (mat[row][i] == 0) {  // Ставим на текущую позицию строку с ненулевым значением
                subtract = false;
                for (size_t j = row + 1; j < mat.rows(); ++j) {
                    if (mat[j][i] != 0) {
                        subtract = true;
                        auto swap_op = std::make_unique<Swap>(row, j);
                        swap_op->apply(mat);
                        res.push_back(std::move(swap_op));
                    }
                }
            }
            if (!subtract) {
                ++d;
                continue;
            }
            if (rnd(mat[row][i] - 1) != 0) {  // Опорные значения должны быть единицами
                auto norm_op = std::make_unique<Normalize>(row, mat[row][i]);
                norm_op->apply(mat);
                res.push_back(std::move(norm_op));
            } else {
                mat[row][i] = 1;
            }

            for (size_t j = 0; j < mat.rows(); ++j) { // Обнуляем столбец
                if (j == row) {
                    continue;
                }
                if (mat[j][i] != 0) {
                    auto sub_op = std::make_unique<Subtract>(row, j, mat[j][i]);
                    sub_op->apply(mat);
                    res.push_back(std::move(sub_op));
                }
            }
        }

        return res;
    }
}

/// @file
