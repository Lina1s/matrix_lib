#ifndef MATRIX_LIB_OPERATIONS_H
#define MATRIX_LIB_OPERATIONS_H

#include "../Matrix.h"

#include <iostream>

namespace gaussian_elimination {
    class GEOperation {
    public:
        virtual void apply(Matrix &matrix) const = 0;

        [[nodiscard]] virtual double det_coefficient() const = 0;

        virtual void print(std::ostream &os) const = 0;

        virtual ~GEOperation();

        friend std::ostream &operator<<(std::ostream &os, const GEOperation &op);
    };

    class Normalize : public GEOperation {
    private:
        int row;
        double scalar;
    public:
        Normalize(int row, double scalar);

        void apply(Matrix &matrix) const override;

        [[nodiscard]] double det_coefficient() const override;

        void print(std::ostream &os) const override;
    };

    class Swap : public GEOperation {
    private:
        int row1;
        int row2;
    public:
        Swap(int row1, int row2);

        void apply(Matrix &matrix) const override;

        [[nodiscard]] double det_coefficient() const override;

        void print(std::ostream &os) const override;
    };

    class Subtract : public GEOperation {
    private:
        int row_source;
        int row_target;
        double scalar;
    public:
        Subtract(int rowSource, int rowTarget, double scalar);

        void apply(Matrix &matrix) const override;

        [[nodiscard]] double det_coefficient() const override;

        void print(std::ostream &os) const override;
    };
}

#endif //MATRIX_LIB_OPERATIONS_H
