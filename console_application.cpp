#include "matrix_lib/matrix_lib.h"

#include <io.h>
#include <fcntl.h>
#include <optional>
#include <cmath>

using namespace matrix_lib;

void cws() {
    std::cin.ignore(256, '\n');
}

Matrix input_matrix(std::optional<size_t> nrows = std::nullopt, std::optional<size_t> ncolumns = std::nullopt) {
    size_t rows;
    if (nrows.has_value()) {
        rows = nrows.value();
        std::wcout << L"В матрице должно быть " << rows << L" строк\n";
    } else {
        std::wcout << L"Введите количество строк в матрице: ";
        std::cin >> rows;
        cws();
    }

    size_t columns;
    if (ncolumns.has_value()) {
        columns = ncolumns.value();
        std::wcout << L"В матрице должно быть " << columns << L" столбцов\n";
    } else {
        std::wcout << L"Введите количество столбцов в матрице: ";
        std::cin >> columns;
        cws();
    }

    std::wcout << L"Введите матрицу поэлементно, слева направо, сверху вниз\n";
    std::vector<std::vector<double>> vec(rows, std::vector(columns, 0.0));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            std::cin >> vec[i][j];
        }
    }
    cws();

    return Matrix(std::move(vec));
}

int await_input(int from, int to) {
    int ans;
    bool correct;
    do {
        std::cin >> ans;
        cws();
        if (ans < from || ans > to) {
            std::wcout << L"Ответ должен лежать в диапазоне от " << from << L" до " << to << L'\n';
            correct = false;
        } else {
            correct = true;
        }
    } while (!correct);
    return ans;
}

void print_matrix(const Matrix &mat) {
    for (size_t i = 0; i < mat.rows(); ++i) {
        for (size_t j = 0; j < mat.columns(); ++j) {
            std::wcout << mat[i][j] << L' ';
        }
        std::wcout << L'\n';
    }
}

void addition() {
    std::wcout << L"Введите первую матрицу: \n";
    Matrix left = input_matrix();
    std::wcout << L"Введите вторую матрицу: \n";
    Matrix right = input_matrix(left.rows(), left.columns());
    std::wcout << L"Результат сложения: \n";
    print_matrix(left + right);
}

void subtraction() {
    std::wcout << L"Введите первую матрицу: \n";
    Matrix left = input_matrix();
    std::wcout << L"Введите вторую матрицу: \n";
    Matrix right = input_matrix(left.rows(), left.columns());
    std::wcout << L"Результат вычитания: \n";
    print_matrix(left - right);
}

void multiplication() {
    std::wcout << L"Введите первую матрицу: \n";
    Matrix left = input_matrix();
    std::wcout << L"Введите вторую матрицу: \n";
    Matrix right = input_matrix(left.columns());
    std::wcout << L"Результат умножения: \n";
    print_matrix(left * right);
}

void multiplication_by_scalar() {
    std::wcout << L"Введите матрицу: \n";
    Matrix mat = input_matrix();
    double x;
    std::wcout << L"введите скаляр: ";
    std::cin >> x;
    std::wcout << L"Результат умножения: \n";
    print_matrix(x * mat);
}

void division() {
    std::wcout << L"Введите матрицу: \n";
    Matrix mat = input_matrix();
    double x;
    std::wcout << L"введите скаляр: ";
    std::cin >> x;
    std::wcout << L"Результат деления: \n";
    print_matrix(mat / x);
}

void transposition() {
    std::wcout << L"Введите матрицу: \n";
    Matrix mat = input_matrix();
    std::wcout << L"Результат транспонирования: \n";
    print_matrix(transpose(mat));
}

void gauss() {
    std::wcout << L"Введите матрицу: \n";
    Matrix mat = input_matrix();
    gaussian_elimination::Operations ops = gaussian_elimination::eliminate_inplace(mat);
    std::wcout << L"Шаги метода Гаусса: \n";
    for (const auto &op: ops) {
        std::wcout << *op << L'\n';
    }
    std::wcout << L"Каноническая форма матрицы: \n";
    print_matrix(mat);
    if (mat.rows() == mat.columns()) {
        double determinant = det_from_canonical(mat, ops);
        std::wcout << L"Определитель матрицы: " << determinant << L'\n';
        if (determinant != 0) {
            Matrix inv = inverse_from_operations(mat.rows(), ops);
            std::wcout << L"Обратная матрица: \n";
            print_matrix(inv);
        }
    }
    size_t rank = rank_from_canonical_form(mat);
    std::wcout << L"Ранг матрицы: " << rank << L'\n';
    if (rank < mat.rows() || rank < mat.columns()) {
        std::wcout << L"Фундаментальная система решений ОСЛАУ матрицы: \n";
        print_matrix(nullspace_from_canonical_form(mat));
    }
    std::wcout << L"Вам хотелось бы найти частное решение соответствующего матричного уравнения?\n"
                  L"1. Да\n"
                  L"2. Нет\n";
    int ans = await_input(1, 2);
    if (ans == 2) {
        return;
    }
    std::wcout << L"Введите матрицу правой части\n";
    Matrix rhs = input_matrix(mat.rows());
    apply_inplace(rhs, ops);
    std::wcout << L"После применения операций справа получится следующая матрица: \n";
    print_matrix(rhs);
}

int main() {
    _setmode(_fileno(stdout), _O_U8TEXT);
    std::wcout << L"Какую возможность вам хотелось бы протестировать?\n"
                  L"1. Сложение матриц\n"
                  L"2. Вычитание матриц\n"
                  L"3. Умножение матриц\n"
                  L"4. Умножение матицы на скаляр\n"
                  L"5. Деление матрицы на скаляр\n"
                  L"6. Транспонирование матрицы\n"
                  L"7. Метод Гаусса\n";

    switch (await_input(1, 7)) {
        case 1:
            addition();
            break;
        case 2:
            subtraction();
            break;
        case 3:
            multiplication();
            break;
        case 4:
            multiplication_by_scalar();
            break;
        case 5:
            division();
            break;
        case 6:
            transposition();
            break;
        case 7:
            gauss();
            break;
    }
    return 0;
}
