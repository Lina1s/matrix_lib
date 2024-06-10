#include "elimination.h"

namespace gaussian_elimination {
    std::vector<std::unique_ptr<GEOperation>> eliminate(const Matrix &matrix) {
        auto copy = matrix;

        size_t min_dim = std::min(copy.rows(), copy.columns());

        std::vector<std::unique_ptr<GEOperation>> res{};
        for (int i = 0; i < min_dim; ++i) {
            bool subtract = true;
            if (copy[i][i] == 0) {  // Ставим на текущую позицию строку с ненулевым значением
                subtract = false;
                for (int j = i + 1; j < copy.rows(); ++j) {
                    if (copy[j][i] != 0) {
                        subtract = true;
                        auto swap_op = std::make_unique<Swap>(i, j);
                        swap_op->apply(copy);
                        res.push_back(std::move(swap_op));
                    }
                }
            }
            if (!subtract) {
                continue;
            }
            if (copy[i][i] != 1) {  // Опорные значения должны быть едницами
                auto norm_op = std::make_unique<Normalize>(i, copy[i][i]);
                norm_op->apply(copy);
                res.push_back(std::move(norm_op));
            }

            for (int j = 0; j < copy.rows(); ++j) { // Обнуляем столбец
                if (j == i) {
                    continue;
                }
                if (copy[j][i] != 0) {
                    auto sub_op = std::make_unique<Subtract>(i, j, copy[j][i]);
                    sub_op->apply(copy);
                    res.push_back(std::move(sub_op));
                }
            }
        }

        return res;
    }
}
