#ifndef MATRIX_LIB_GAUSSIAN_BASED_H
#define MATRIX_LIB_GAUSSIAN_BASED_H

#include "gaussian_elimination/elimination.h"

void apply_inplace(Matrix &mat, const gaussian_elimination::Operations &ops);

Matrix apply(const Matrix &mat, const gaussian_elimination::Operations &ops);

double det_from_canonical(const Matrix &canonical_form, const gaussian_elimination::Operations &ops);

double det(const Matrix &matrix);

size_t rank_from_canonical_form(const Matrix &canonical_form);

size_t rank(const Matrix &mat);

std::vector<std::vector<double>> nullspace_from_canonical_form(const Matrix &canonical_form, size_t rank);

std::vector<std::vector<double>> nullspace_from_canonical_form(const Matrix &canonical_form);

std::vector<std::vector<double>> nullspace(const Matrix &matrix);

#endif //MATRIX_LIB_GAUSSIAN_BASED_H