#ifndef MATRIX_LIB_OPERATIONS_H
#define MATRIX_LIB_OPERATIONS_H

///@cond
#include "../Matrix.h"

#include <iostream>
///@endcond
namespace matrix_lib::gaussian_elimination {
    /**
     * @brief Абстрактный класс операции метода Гаусса
     * @details Метод Гаусса - последовательное применение 3-х операций: умножения строки матрицы на скаляр,
     * обмен строк матрицы местами, вычитание из одной строки матрицы другой строки.
     * В библиотеке matrix_lib каждая операция представляет собой объект одного из наследников данного класса.
     */
    class Operation {
    public:
        /**
         * @brief Применяет операцию к матрице
         * @param[in,out] matrix
         */
        virtual void apply(Matrix &matrix) const = 0;

        /**
         * @brief Определяет, как применение операции влияет на определитель матрицы
         * @return Возвращает такое число @f$x@f$, что @f$\text{det}(matrix) = x\cdot \text{det}(apply(matrix)) @f$
         */
        [[nodiscard]] virtual double det_coefficient() const = 0;

        virtual void print(std::wostream &os) const = 0;
        /**
         * @brief Вывод строкового представления в поток
         * @param os Поток вывода
         */
        virtual void print(std::ostream &os) const = 0;

        virtual ~Operation();

        friend std::wostream &operator<<(std::wostream &, const Operation &op);
    };

    /**
     * @brief Операция деления строки на скаляр
     */
    class Normalize : public Operation {
    private:

        size_t row;
        double scalar;
    public:
        /**
         * @param row Номер строки, которую нужно поделить
         * @param scalar Скаляр, на который нужно поделить строку
         */
        Normalize(size_t row, double scalar);

        void apply(Matrix &matrix) const override;

        [[nodiscard]] double det_coefficient() const override;

        void print(std::wostream &os) const override;
    };

    /**
     * @brief Операция обмена строк местами
     */
    class Swap : public Operation {
    private:
        size_t row1;
        size_t row2;
    public:
        /**
         * @param row1 Первая строка матрицы
         * @param row2 Вторая строка матрицы
         */
        Swap(size_t row1, size_t row2);

        void apply(Matrix &matrix) const override;

        [[nodiscard]] double det_coefficient() const override;

        void print(std::wostream &os) const override;
    };

    /**
     * @brief Операция вычитания одной строки из другой
     */
    class Subtract : public Operation {
    private:
        size_t row_source;
        size_t row_target;
        double scalar;
    public:
        /**
         * @param rowSource Строка, которую нужно вычесть
         * @param rowTarget Строка, из которой нужно вычесть другую строку
         * @param scalar Коэффициент, на который будет домножено вычитаемое
         */
        Subtract(size_t rowSource, size_t rowTarget, double scalar);

        void apply(Matrix &matrix) const override;

        [[nodiscard]] double det_coefficient() const override;

        void print(std::wostream &os) const override;
    };
}

#endif //MATRIX_LIB_OPERATIONS_H
///@file
