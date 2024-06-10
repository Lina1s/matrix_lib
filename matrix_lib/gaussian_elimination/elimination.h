#ifndef MATRIX_LIB_ELIMINATION_H
#define MATRIX_LIB_ELIMINATION_H

#include "operations.h"

#include <memory>

namespace gaussian_elimination {
    std::vector<std::unique_ptr<GEOperation>> eliminate(const Matrix& matrix);
}

#endif //MATRIX_LIB_ELIMINATION_H
