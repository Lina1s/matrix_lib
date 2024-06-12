#ifndef MATRIX_LIB_MATRIX_H
#define MATRIX_LIB_MATRIX_H
///@cond
#include <vector>
///@endcond
namespace matrix_lib {
    /**
     * @brief Класс матрицы
     * @details
     * Основной класс библиотеки matrix_lib
     */
    class Matrix {
    private:
        std::vector<std::vector<double>> inner;

        static bool is_matrix(const std::vector<std::vector<double>> &mat);

    public:
        /**
         * @brief Конструктор по умолчанию
         * @details Создает пустую матрицу
         */
        Matrix();
        /**
         * @name Конструкторы на основе векторов
         * @details
         * Конструкторы, позволяющие представить двумерный вектор double в виде матрицы.
         * В случае, если строки в векторе имеют разный размер, будет выброшено исключение VectorException
         * @param mat Двумерный вектор, представляющий матрицу
         */
         ///@{
        explicit Matrix(const std::vector<std::vector<double>> &mat);

        explicit Matrix(std::vector<std::vector<double>> &&mat);

        Matrix(std::initializer_list<std::vector<double>> rows);

        Matrix &operator=(const std::vector<std::vector<double>> &mat);

        Matrix &operator=(std::vector<std::vector<double>> &&mat);
        ///@}
        /**
         * @name Конструкторы копирования и перемещения
         * @param[in] other Ссылка на копируемую матрицу
         */
         ///@{
        Matrix(const Matrix &other);

        Matrix(Matrix &&other) noexcept;

        Matrix &operator=(const Matrix &other);

        Matrix &operator=(Matrix &&other) noexcept;
        ///@}

        /**
         * @name Доступ по индексу
         * @details
         * Получение строки матрицы по индексу, начиная с 0. В случае, если индекс выходит за пределы матрицы,
         * будет выброшено исключение std::out_of_range
         * @param[in] x Индекс строки
         * @return Вектор строка матрицы
         */
         ///@{
        std::vector<double> &operator[](size_t x);

        const std::vector<double> &operator[](size_t x) const;
        ///@}

        /**
         * @brief Количество строк в матрице
         * @return Количество строк в матрице
         */
        [[nodiscard]] size_t rows() const;

        /**
         * @brief Количество столбцов в матрице
         * @return Количество столбцов в матрице
         */
        [[nodiscard]] size_t columns() const;

        /**
         * @name Математические операции "на месте"
         * @brief Математические операции, изменяющие левый операнд
         * @return Ссылку на левый операнд
         */
         ///@{
         /**
          * @brief Сложение матриц
          * @details
          */
        Matrix &operator+=(const Matrix &other);

        /**
          * @brief Вычитание матриц
          * @details
          */
        Matrix &operator-=(const Matrix &other);

        /**
         * @brief Умножение матрицы на скаляр
         * @details
         */
        Matrix &operator*=(double scalar);

        /**
         * @brief Деление матрицы на скаляр
         * @details При попытке деления на 0 будет выброшено исключение std::overflow_error
         */
        Matrix &operator/=(double scalar);
        ///@}

        /**
         * @brief Транспонирует матрицу "на месте"
         * @details
         * @param[in,out] mat Матрица, которую нужно транспонировать
         */
        friend void transpose_inplace(Matrix &mat);

        /**
         * @brief Создает единичную матрицу
         * @details
         * @param[in] n Размер возвращаемой матрицы
         * @return Единичную матрицу размера n @f$\times@f$ n
         */
        static Matrix identity(size_t n);

        /**
         * @brief Сравнение матриц на равенство
         * @details Поэлементно проверяет матрицы на равенство
         * @param other Матрица, с которой нужно сравнить this
         */
         ///@{
        bool operator==(const Matrix &other) const;
        bool operator!=(const Matrix &other) const;
        ///@}
    };

    /**
     * @brief Транспонирование матрицы
     * @details Создает копию матрицы mat и транспонирует ее
     * @param[in] mat Матрица, котору нужно транспонировать
     * @return Транспонированная копия переданной матрицы
     */
    Matrix transpose(const Matrix &mat);

    /**
     * @name Арифметические операции, не изменяющие передаваемые матрицы
     * @return Новую матрицу - результат арифметической операции
     */
    ///@{
    /// Унарный плюс
    Matrix operator+(const Matrix &mat);

    /// Унарный минус
    Matrix operator-(const Matrix &mat);

    /// Сложение матриц
    Matrix operator+(const Matrix &lhs, const Matrix &rhs);

    /// Вычитание матриц
    Matrix operator-(const Matrix &lhs, const Matrix &rhs);

    /// Умножение матрицы на скаляр
    Matrix operator*(const Matrix &lhs, double rhs);
    /// Умножение матрицы на скаляр
    Matrix operator*(double lhs, const Matrix &rhs);

    /**
     * @brief Умножение матриц
     * @details При попытке умножения матриц с несовместимыми размерами будет выброшено исключение ShapeError
     */
    Matrix operator*(const Matrix &lhs, const Matrix &rhs);

    /**
     * @brief Деление матрицы на скаляр
     * @details При попытке деления на 0 будет выброшено исключение std::overflow_error
     */
    Matrix operator/(const Matrix &lhs, double rhs);
    ///@}
}

#endif //MATRIX_LIB_MATRIX_H
///@file
