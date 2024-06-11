//
// Created by timur on 12.06.2024.
//

#include "exceptions.h"

matrix_lib::MatrixLibError::MatrixLibError(const std::string &arg) : runtime_error(arg) {}

matrix_lib::ShapeError::ShapeError(const std::string &arg) : MatrixLibError(arg) {}

matrix_lib::InvalidOperationError::InvalidOperationError(const std::string &arg) : MatrixLibError(arg) {}

matrix_lib::VectorError::VectorError(const std::string &arg) : MatrixLibError(arg) {}
