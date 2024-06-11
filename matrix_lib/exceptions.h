#ifndef MATRIX_LIB_EXCEPTIONS_H
#define MATRIX_LIB_EXCEPTIONS_H

#include <stdexcept>

namespace matrix_lib {
    struct MatrixLibError : public std::runtime_error {
        explicit MatrixLibError(const std::string &arg);
    };

    struct VectorError : public MatrixLibError {
        explicit VectorError(const std::string &arg);
    };

    struct ShapeError : public MatrixLibError {
        explicit ShapeError(const std::string &arg);
    };

    struct InvalidOperationError : public MatrixLibError {
        explicit InvalidOperationError(const std::string &arg);
    };
}

#endif //MATRIX_LIB_EXCEPTIONS_H
