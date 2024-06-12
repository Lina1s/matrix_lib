#ifndef MATRIX_LIB_GAUSSIAN_BASED_H
#define MATRIX_LIB_GAUSSIAN_BASED_H
///@cond
#include "gaussian_elimination/elimination.h"

///@endcond
namespace matrix_lib {
    /**
     * @brief Применяет операции метода Гаусса "На месте"
     * @param[in,out] mat Матрица, к которой нужно применить операции
     * @param ops Операции метода Гаусса, которые нужно применить
     */
    void apply_inplace(Matrix &mat, const gaussian_elimination::Operations &ops);

    /**
     * @brief Применяет операции метода Гаусса
     * @param[in] mat Матрица, к которой нужно применить операции
     * @param[in] ops Операции метода Гаусса, которые нужно применить
     * @return Матрица, полученная применением операций ops к матрице mat
     */
    Matrix apply(const Matrix &mat, const gaussian_elimination::Operations &ops);
    /**
     * @brief На основе канонической формы матрицы и операций метода Гаусса вычисляет определитель матрицы
     * @param canonical_form Каноническая форма матрицы
     * @param ops Операции метода Гаусса, которые привели матрицу к указанной канонической форме
     * @return Определитель матрицы, применение операций ops к которой приводит ее к канонической форме canonical_form.
     * Если такой матрицы не существует или canonical_form не является канонической формой какой-либо матрицы,
     * результат функции не уточнен.
     */
    double det_from_canonical(const Matrix &canonical_form, const gaussian_elimination::Operations &ops);

    /**
     * @brief Вычисляет определитель матрицы
     * @details При попытке применения к неквадратной матрице будет выброшено исключение ShapeError
     * @param matrix Матрица, определитель которой нужно вычислить
     * @return
     */
    double det(const Matrix &matrix);

    /**
     * @brief Вычисляет ранг матрицы в канонической форме
     * @param canonical_form Матрица в канонической форме
     * @return Ранг матрицы. В случае, если canonical_form не в канонической форме, результат не уточнен
     */
    size_t rank_from_canonical_form(const Matrix &canonical_form);

    /**
     * @brief Вычисляет ранг матрицы
     * @param mat Матрица, ранг которой нужно вычислить
     * @return Ранг матрицы
     */
    size_t rank(const Matrix &mat);

    /**
     * @brief Вычисляет ФСР матрицы в канонической форме с указанным рангом
     * @detail Если ранг переданной матрицы не совпадает с переданным рангом, поведение этой функции не
     * определено
     * @param canonical_form Матрица в канонической формы
     * @param rank Ранг матрицы canonical_form
     * @return ФСР матрицы canonical_form, т.е. максимальную по размеру матрицу с максимальным рангом A такую, что
     * @f$A\cdot canonical_form = 0@f$, или пустую матрицу, если canonical_from невырожденная.
     * Если canonical_form не в канонической форме, результат не уточнен
     */
    Matrix nullspace_from_canonical_form(const Matrix &canonical_form, size_t rank);

    /**
     * @brief Вычисляет ФСР матрицы в канонической форме
     * @param canonical_form Матрица в канонической формы
     * @return ФСР матрицы canonical_form, т.е. максимальную по размеру матрицу с максимальным рангом A такую, что
     * @f$A\cdot canonical_form = 0@f$, или пустую матрицу, если canonical_from невырожденная.
     * Если canonical_form не в канонической форме, результат не уточнен
     */
    Matrix nullspace_from_canonical_form(const Matrix &canonical_form);

    /**
     * @brief Вычисляет ФСР матрицы
     * @param matrix Матрица, ФСР которой нужно вычислить
     * @return ФСР матрицы matrix, т.е. максимальную по размеру матрицу с максимальным рангом A такую, что
     * @f$A\cdot matrix = 0@f$, или пустую матрицу, если matrix невырожденная.
     */
    Matrix nullspace(const Matrix &matrix);

    /**
     * @brief Вычисляет обратную матрицу по операциям методам Гаусса
     * @param n Размер квадратной матрицы
     * @param ops Операции метода Гаусса
     * @return Матрица, обратная такой матрице X, что apply(X, ops) поэлементно совпадает с Matrix::identical(n).
     * Если такой матрицы не существует, результат не уточнен
     */
    Matrix inverse_from_operations(size_t n, const gaussian_elimination::Operations &ops);

    /**
     * @brief Вычисляет матрицу, обратную данной
     * @details При попытке найти обратную матрицу неквадратной матрицы будет выброшено исключение ShapeError.
     * При попытке найти обратную матрицу вырожденной матрицы будет выброшено исключение InvalidOperationError.
     * @param mat Матрица, обратную к которой нужно найти
     * @return Матрица, обратная к mat
     */
    Matrix inverse(const Matrix &mat);
}
#endif //MATRIX_LIB_GAUSSIAN_BASED_H
///@file
