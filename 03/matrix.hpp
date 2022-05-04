#pragma once
#include <iostream>

class Matrix{
private:
    size_t rows_;
    size_t cols_;
    int32_t **data_;
public:
    class ProxyRow
    {
    private:
        int32_t *data_;
        size_t size;
    public:
        ProxyRow(int32_t *row, size_t cols);
        int32_t& operator[](size_t j) const;
    };

    Matrix(size_t n, size_t m);
    size_t getRows() const;
    size_t getCols() const;
    Matrix& operator*=(int32_t x);
    Matrix operator+(const Matrix& a);
    friend std::ostream& operator<<(std::ostream &os, const Matrix& a);
    ProxyRow operator[](size_t i) const;
    bool operator==(const Matrix& a) const;
    bool operator!=(const Matrix& a) const;
    ~Matrix();
};