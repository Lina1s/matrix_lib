#ifndef MATRIX_LIB_EXCEPTIONS_H
#define MATRIX_LIB_EXCEPTIONS_H

///@cond
#include <stdexcept>
///@endcond
namespace matrix_lib {
    /**
     * @brief Базовое исключение библиотеки matrix_lib
     */
    struct MatrixLibError : public std::runtime_error {
        explicit MatrixLibError(const std::string &arg);
    };

    /**
     * @brief Исключение, возникающее при попытке преобразовать вектор неправильной формы в матрицу
     */
    struct VectorError : public MatrixLibError {
        explicit VectorError(const std::string &arg);
    };

    /**
     * @brief Исключение, возникающее при попытке применить операцию к матрице неправильного размера
     */
    struct ShapeError : public MatrixLibError {
        explicit ShapeError(const std::string &arg);
    };

    /**
     * @brief Исключение, возникающее при попытке применения неприменимой операции к матрице
     */
    struct InvalidOperationError : public MatrixLibError {
        explicit InvalidOperationError(const std::string &arg);
    };
}

#endif //MATRIX_LIB_EXCEPTIONS_H
///@file
