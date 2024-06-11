#ifndef MATRIX_LIB_ELIMINATION_H
#define MATRIX_LIB_ELIMINATION_H

#include "operations.h"

#include <memory>

namespace gaussian_elimination {
    using Operations = std::vector<std::unique_ptr<Operation>>;

    Operations eliminate_inplace(Matrix &mat);
    Operations eliminate(const Matrix &matrix);
}

#endif //MATRIX_LIB_ELIMINATION_H
