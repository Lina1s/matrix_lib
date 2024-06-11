#include "elimination.h"

namespace gaussian_elimination {
    std::vector<std::unique_ptr<Operation>> eliminate_inplace(Matrix &mat) {

        std::vector<std::unique_ptr<Operation>> res{};
        size_t d = 0;
        for (size_t i = 0; i < mat.columns(); ++i) {
            bool subtract = true;
            size_t row = i - d;
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
            if (mat[row][i] != 1) {  // Опорные значения должны быть едницами
                auto norm_op = std::make_unique<Normalize>(row, mat[row][i]);
                norm_op->apply(mat);
                res.push_back(std::move(norm_op));
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

    std::vector<std::unique_ptr<Operation>> eliminate(const Matrix &matrix) {
        auto copy = matrix;
        return eliminate_inplace(copy);
    }
}
