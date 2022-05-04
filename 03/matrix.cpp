#include "matrix.hpp"

Matrix::Matrix(size_t n, size_t m){
    rows_ = n;
    cols_ = m;

    data_ = new int32_t*[rows_];
    for(size_t i = 0; i < rows_; i++)
        data_[i] = new int32_t[cols_];
}

size_t Matrix::getRows() const{
    return rows_;
}

size_t Matrix::getCols() const{
    return cols_;
}

bool Matrix::operator==(const Matrix& a) const{

    if(rows_ != a.rows_ || cols_ != a.cols_)
        return false;

    for(size_t i = 0; i < rows_; i++){
        for(size_t j = 0; j < cols_; j++){
            if (data_[i][j] != a.data_[i][j])
                return false;
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& a) const{
    if(*this == a)
        return true;
    
    return false;
}

Matrix& Matrix::operator*=(int32_t x){

    for(size_t i = 0; i < rows_; i++){
        for(size_t j = 0; j < cols_; j++){
            data_[i][j] *= x;
        }
    }

    return *this;
}

Matrix Matrix::operator+(const Matrix &a){
    if (rows_ != a.rows_ || cols_ != a.cols_){
        throw std::out_of_range("Wrong dimensions");
    }
    
    Matrix result = Matrix(rows_, cols_);

    for(size_t i = 0; i < rows_; i++){
        for(size_t j = 0; j < cols_; j++){
            result.data_[i][j] = data_[i][j] + a.data_[i][j];
        }
    }

    return result;
}

std::ostream& operator<<(std::ostream &os, const Matrix& a) {

    for (size_t i = 0; i < a.getRows(); i++){
        for(size_t j = 0; j < a.getCols(); j++){
            if (j != a.getCols()-1){
                os << a[i][j] << " ";
            }
            else{
                os << a[i][j];
            }
        }
        if (i != a.getRows()-1){
            os << std::endl;
        }
    }
        
    return os;
}

Matrix::ProxyRow::ProxyRow(int32_t *row, size_t cols){
    data_ = row;
    size = cols;
}

int32_t& Matrix::ProxyRow::operator[](size_t j) const{
    
    if(j >= size){
        throw std::out_of_range("Out of range");
    }

    return data_[j];
}

Matrix::ProxyRow Matrix::operator[](size_t i) const{

    if(i >= rows_){
        throw std::out_of_range("Out of range");
    }

    return ProxyRow(data_[i], cols_);
}

Matrix::~Matrix(){
    if (data_ != nullptr){
        for(size_t i = 0; i < rows_; i++){
            if(data_[i] != nullptr){
                delete[] data_[i];
            }
        }
        delete[] data_;
    }
}