#ifndef MATRIX_LIB_OPERATIONS_H
#define MATRIX_LIB_OPERATIONS_H

#include "../Matrix.h"

#include <iostream>

namespace matrix_lib::gaussian_elimination {
    class Operation {
    public:
        virtual void apply(Matrix &matrix) const = 0;

        [[nodiscard]] virtual double det_coefficient() const = 0;

        virtual void print(std::wostream &os) const = 0;

        virtual ~Operation();

        friend std::wostream &operator<<(std::wostream &, const Operation &op);
    };

    class Normalize : public Operation {
    private:
        size_t row;
        double scalar;
    public:
        Normalize(size_t row, double scalar);

        void apply(Matrix &matrix) const override;

        [[nodiscard]] double det_coefficient() const override;

        void print(std::wostream &os) const override;
    };

    class Swap : public Operation {
    private:
        size_t row1;
        size_t row2;
    public:
        Swap(size_t row1, size_t row2);

        void apply(Matrix &matrix) const override;

        [[nodiscard]] double det_coefficient() const override;

        void print(std::wostream &os) const override;
    };

    class Subtract : public Operation {
    private:
        size_t row_source;
        size_t row_target;
        double scalar;
    public:
        Subtract(size_t rowSource, size_t rowTarget, double scalar);

        void apply(Matrix &matrix) const override;

        [[nodiscard]] double det_coefficient() const override;

        void print(std::wostream &os) const override;
    };
}

#endif //MATRIX_LIB_OPERATIONS_H
