#ifndef MATRIX_LIB_ELIMINATION_H
#define MATRIX_LIB_ELIMINATION_H

///@cond
#include "operations.h"

#include <memory>
///@endcond
/**
 * @brief Пространство имен, содержащее функции и классы для применения метода Гаусса
 */
namespace matrix_lib::gaussian_elimination {
    /**
     * @brief Сокращение для типа возвращаемого значения функции eliminate_inplace
     */
    using Operations = std::vector<std::unique_ptr<Operation>>;

    /**
     * @brief Применяет метод Гаусса к матрице "на месте"
     * @details Изменяет переданную матрицу, приводя ее к каноническому виду
     * @param[in,out] mat Матрица, к которой будет применен метод Гаусса
     * @return Список операций метода Гаусса
     */
    Operations eliminate_inplace(Matrix &mat);

    Operations eliminate(const Matrix &matrix);
}

#endif //MATRIX_LIB_ELIMINATION_H
///@file
