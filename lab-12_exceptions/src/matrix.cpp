#include "matrix.h"

#include <iostream>

Matrix::Matrix() {
    rows_ = 0;
    cols_ = 0;
    data_ = nullptr;
}

void Matrix::delete_(int **data, size_t allocated_rows) {
    if (data == nullptr) {
        return;
    }

    for (size_t allocated_row = 0; allocated_row < allocated_rows; ++allocated_row) {
        delete[] data[allocated_row];
    }

    delete[] data;
}

Matrix::~Matrix() {
    delete_(data_, rows_);
}

void Matrix::load(const std::string &file_name) {
    std::ifstream in(file_name);

    if (!in.is_open()) {
        throw MatrixException("LOAD: unable to open file.");
    }

    size_t new_rows;
    if (!(in >> new_rows)) {
        throw MatrixException("LOAD: invalid file format.");
    }

    size_t new_cols;
    if (!(in >> new_cols)) {
        throw MatrixException("LOAD: invalid file format.");
    }

    size_t allocated_rows = 0;
    int **new_data = nullptr;

    try {
        new_data = new int *[new_rows];
        for (size_t row = 0; row < new_rows; ++row) {
            new_data[row] = new int[new_cols];
            ++allocated_rows;
            for (size_t col = 0; col < new_cols; ++col) {
                if (!(in >> new_data[row][col])) {
                    delete_(new_data, allocated_rows);

                    throw MatrixException("LOAD: invalid file format.");
                }
            }
        }

        delete_(data_, rows_);

        rows_ = new_rows;
        cols_ = new_cols;
        data_ = new_data;
    } catch (std::bad_alloc const&) {
        delete_(data_, allocated_rows);

        throw MatrixException("Unable to allocate memory.");
    }

    in.close();
}

void Matrix::print(std::ostream &out) const {
    for (size_t row = 0; row < rows_; ++row) {
        for (size_t col = 0; col < cols_; ++col) {
            if (col > 0) {
                out << " ";
            }
            out << data_[row][col];
        }
        out << std::endl;
    }
}

void Matrix::add(const Matrix &other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw MatrixException("ADD: dimensions do not match.");
    }

    for (size_t row = 0; row < rows_; ++row) {
        for (size_t col = 0; col < cols_; ++col) {
            data_[row][col] += other.data_[row][col];
        }
    }
}

void Matrix::mul(const Matrix &other) {
    if (cols_ != other.rows_) {
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }

    size_t allocated_rows = 0;
    int **result = nullptr;

    try {
        result = new int *[rows_];
        for (size_t row = 0; row < rows_; ++row) {
            result[row] = new int[other.cols_];
            ++allocated_rows;
            for (size_t col = 0; col < other.cols_; ++col) {
                result[row][col] = 0;
                for (size_t com = 0; com < cols_; ++com) {
                    result[row][col] += data_[row][com] * other.data_[com][col];
                }
            }
        }

        delete_(data_, rows_);

        cols_ = other.cols_;
        data_ = result;
    } catch (std::bad_alloc const&) {
        delete_(result, allocated_rows);

        throw MatrixException("Unable to allocate memory.");
    }
}

void Matrix::elem(std::ostream &out, int row, int col) const {
    if (row < 0 || row >= (int) rows_ || col < 0 || col >= (int) cols_) {
        throw MatrixException("ACCESS: bad index.");
    }

    out << data_[row][col] << std::endl;
}
