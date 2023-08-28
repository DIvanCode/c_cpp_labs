#pragma once

#include <cstddef>
#include <fstream>
#include <utility>

class MatrixException: public std::exception {
public:
    explicit MatrixException(std::string message): msg_(std::move(message)) {}
    const char* what() const noexcept override { return msg_.c_str();}
private:
    std::string msg_;
};

class Matrix {
public:
    Matrix();
    ~Matrix();

    void load(const std::string &file_name);
    void print(std::ostream &out) const;
    void add(const Matrix &other);
    void mul(const Matrix &other);
    void elem(std::ostream &out, int row, int col) const;

private:
    size_t rows_;
    size_t cols_;
    int **data_;

    static void delete_(int **data, size_t allocated_rows);
};