#include "matrix.h"

#include <cstring>
#include <stdexcept>

Matrix::Matrix(size_t r, size_t c) {
    _rows = r;
    _cols = c;
    _data = new int *[_rows];
    for (size_t row = 0; row < _rows; ++row) {
        _data[row] = new int[_cols];
        memset(_data[row], 0, _cols * sizeof(int));
    }
}

Matrix::Matrix(const Matrix &m) {
    _rows = m.get_rows();
    _cols = m.get_cols();
    _data = new int *[_rows];
    for (size_t row = 0; row < _rows; ++row) {
        _data[row] = new int[_cols];
        for (size_t col = 0; col < _cols; ++col) {
            _data[row][col] = m.get(row, col);
        }
    }
}

Matrix& Matrix::operator=(const Matrix &m) {
    if (*this == m) {
        return *this;
    }

    for (size_t row = 0; row < _rows; ++row) {
        delete[] _data[row];
    }
    delete[] _data;

    _rows = m.get_rows();
    _cols = m.get_cols();
    _data = new int *[_rows];
    for (size_t row = 0; row < _rows; ++row) {
        _data[row] = new int[_cols];
        for (size_t col = 0; col < _cols; ++col) {
            _data[row][col] = m.get(row, col);
        }
    }

    return *this;
}

Matrix::~Matrix() {
    for (size_t row = 0; row < _rows; ++row) {
        delete[] _data[row];
    }
    delete[] _data;
}

size_t Matrix::get_rows() const {
    return _rows;
}

size_t Matrix::get_cols() const {
    return _cols;
}

void Matrix::set(size_t i, size_t j, int val) {
    if (i >= _rows || j >= _cols) {
        throw std::runtime_error("Index out of range");
    }

    _data[i][j] = val;
}

int Matrix::get(size_t i, size_t j) const {
    if (i >= _rows || j >= _cols) {
        throw std::runtime_error("Index out of range");
    }

    return _data[i][j];
}

void Matrix::print(FILE *f) const {
    if (f == nullptr) {
        throw std::runtime_error("Bad file");
    }

    for (size_t row = 0; row < _rows; ++row) {
        for (size_t col = 0; col < _cols; ++col) {
            if (col != 0) fprintf(f, " ");
            fprintf(f, "%d", _data[row][col]);
        }
        fprintf(f, "\n");
    }
}

Matrix Matrix::operator+(const Matrix& m) const {
    if (_rows != m.get_rows() || _cols != m.get_cols()) {
        throw std::runtime_error("Sizes are different");
    }

    Matrix res(_rows, _cols);
    for (size_t row = 0; row < _rows; ++row) {
        for (size_t col = 0; col < _cols; ++col) {
            res.set(row, col, _data[row][col] + m.get(row, col));
        }
    }

    return res;
}

Matrix Matrix::operator-(const Matrix& m) const {
    if (_rows != m.get_rows() || _cols != m.get_cols()) {
        throw std::runtime_error("Sizes are different");
    }

    Matrix res(_rows, _cols);
    for (size_t row = 0; row < _rows; ++row) {
        for (size_t col = 0; col < _cols; ++col) {
            res.set(row, col, _data[row][col] - m.get(row, col));
        }
    }

    return res;
}

Matrix Matrix::operator*(const Matrix& m) const {
    if (_cols != m.get_rows()) {
        throw std::runtime_error("Cannot multiply matrices, sizes do not match");
    }

    Matrix res(_rows, m.get_cols());
    for (size_t row = 0; row < res.get_rows(); ++row) {
        for (size_t col = 0; col < res.get_cols(); ++col) {
            int sum = 0;
            for (size_t t = 0; t < _cols; ++t) {
                sum += _data[row][t] * m.get(t, col);
            }
            res.set(row, col, sum);
        }
    }

    return res;
}

Matrix& Matrix::operator+=(const Matrix& m) {
    if (_rows != m.get_rows() || _cols != m.get_cols()) {
        throw std::runtime_error("Sizes are different");
    }

    return *this = *this + m;
}

Matrix& Matrix::operator-=(const Matrix& m) {
    if (_rows != m.get_rows() || _cols != m.get_cols()) {
        throw std::runtime_error("Sizes are different");
    }

    return *this = *this - m;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    if (_cols != m.get_rows()) {
        throw std::runtime_error("Cannot multiply matrices, sizes do not match");
    }

    return *this = *this * m;
}

bool Matrix::operator==(const Matrix& m) const {
    if (this == &m) {
        return true;
    }

    if (_rows != m.get_rows() || _cols != m.get_cols()) {
        return false;
    }

    for (size_t row = 0; row < _rows; ++row) {
        for (size_t col = 0; col < _cols; ++col) {
            if (_data[row][col] != m.get(row, col)) {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& m) const {
    return !(*this == m);
}