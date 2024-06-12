//
// Created by timur on 12.06.2024.
//
///@cond
#include "exceptions.h"
///@endcond
/// @headerfile exceptions.h
matrix_lib::MatrixLibError::MatrixLibError(const std::string &arg) : runtime_error(arg) {}

/// @headerfile exceptions.h
matrix_lib::ShapeError::ShapeError(const std::string &arg) : MatrixLibError(arg) {}

/// @headerfile exceptions.h
matrix_lib::InvalidOperationError::InvalidOperationError(const std::string &arg) : MatrixLibError(arg) {}

/// @headerfile exceptions.h
matrix_lib::VectorError::VectorError(const std::string &arg) : MatrixLibError(arg) {}
///@file
