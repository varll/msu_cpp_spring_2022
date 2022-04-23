#include "BigInt.hpp"
#include <algorithm> 


BigInt::BigInt(){
    data = new char[1];
    data[0] = '0';
    sign = 0;
    size = 1;
}

BigInt::BigInt(const BigInt &x){
    data = new char[x.size];
    std::copy(x.data, x.data + x.size, data);
    size = x.size;
    sign = x.sign;
}

BigInt::BigInt(int32_t x){
    if (x == 0){
        data = new char[1];
        data[0] = '0';
        size = 1;
        sign = 0;
    }
    else{
        sign = 0;
        if (x < 0){
            sign = 1;
            x = -x;
        }
        int32_t x_copy = x;
        size = 0;
        while(x_copy > 0){
            size++;
            x_copy /= 10;
        }
        data = new char[size];
        for(size_t i = 0; i < size; i++){
            data[i] = x % 10 + '0';
            x /= 10;
        }
    }
}

BigInt::BigInt(const std::string &x){
    if (x[0] == '-'){
        data = new char[x.size() - 1];
        std::reverse_copy(x.begin() + 1, x.end(), data);
        size = x.size() - 1;
        sign = 1;
    }
    else{
        data = new char[x.size()];
        std::reverse_copy(x.begin(), x.end(), data);
        size = x.size();
        sign = 0;
    }
}

BigInt BigInt::add(const BigInt &x, const BigInt &y){
    size_t result_size = std::max(x.size, y.size);
    int x_digit, y_digit, sum, offset = 0;
    char *result = new char[result_size + 1];
    for(size_t i = 0; i < result_size; i++){
        x_digit = 0;
        y_digit = 0;

        if (i < x.size){
            x_digit = x.data[i] - '0';
        }
        if(i < y.size){
            y_digit = y.data[i] - '0';
        }

        sum = x_digit + y_digit + offset;
        result[result_size - i] = sum % 10 + '0';
        offset = sum / 10;
    }

    if (offset > 0){
        result[0] = offset + '0';
        BigInt res = BigInt(std::string(result, result_size + 1));
        res.sign = x.sign;
        delete[] result;
        return res;
    }
    else{
        char *result_fix = new char[result_size];
        std::copy(result + 1, result + result_size + 1, result_fix);
        delete[] result;
        BigInt res = BigInt(std::string(result_fix, result_size));
        res.sign = x.sign;
        delete[] result_fix;
        return res;
    }
    
}

BigInt BigInt::sub(const BigInt &x, const BigInt &y){
    int diff = 0, offset = 0, x_digit, y_digit, len = x.size - 1;
    char *result = new char[x.size];

    for(size_t i = 0; i < x.size; i++){
        x_digit = 0;
        y_digit = 0;

        if (i < x.size){
            x_digit = x.data[i] - '0';
        }
        if(i < y.size){
            y_digit = y.data[i] - '0';
        }

        diff = x_digit - y_digit + offset;
        if(diff < 0){
            diff += 10;
            offset = -1;
        }
        else{
            offset = 0;
        }
        result[x.size - 1 - i] = diff + '0';
    }
    for(size_t i = 0; i < x.size; i++){
        if (result[i] != '0'){
            len = i;
            break;
        }
    }
    char *result_fix = new char[x.size - len];
    std::copy(result + len, result + x.size, result_fix);
    delete[] result;
    BigInt res = BigInt(std::string(result_fix, x.size - len));
    res.sign = x.sign;
    delete[] result_fix;
    return res;
}

BigInt BigInt::operator-(){
    BigInt result = *this;
    result.sign = !sign;

    return result;
}

BigInt BigInt::operator+(const BigInt &x){
    if (sign == x.sign){
        return add(*this, x);
    }
    else{
        if(sign){
            return sub(x, *this);
        }
        else{
            return sub(*this, x);
        }
    }
}

BigInt BigInt::operator-(const BigInt &x){
    if (sign == x.sign){
        if(sign == 1){
            return add(*this, x);
        }
        else{
            return sub(*this, x);
        }
    }
    else{
        if(sign == 1){
            return sub(x, *this);
        }
        else{
            return add(*this, x);
        }
    }

}

BigInt BigInt::operator+(const int32_t x){
    return *this + BigInt(x);
}

BigInt BigInt::operator-(const int32_t x){
    return *this - BigInt(x);
}

//Умножение в столбик
BigInt BigInt::operator*(const BigInt &x){
    size_t result_size = this->size + x.size;
    char *result = new char[result_size];
    for(size_t i = 0; i < result_size; i++){
        result[i] = '0';
    }

    int mul = 0, offset = 0, x_digit, y_digit;

    for (size_t j = 0; j < x.size; j++) {
        y_digit = x.data[j] - '0';
        for (size_t i = 0; i < this->size; i++) {
            x_digit = this->data[i] - '0';
    
            int num_zeros = i + j;
            offset = result[num_zeros] - '0';
            mul = x_digit * y_digit + offset;
            result[num_zeros] = (mul % 10) + '0';
            result[num_zeros + 1] += (mul / 10);
        }
    }
    std::reverse(result, result + result_size);
    int len = result_size - 1;
    for (size_t i = 0; i < result_size; i++){
        if(result[i] != '0'){
            len = i;
            break;
        }
    }

    BigInt res = BigInt(std::string(result + len, result_size - len));
    if(this->sign != x.sign){
        res.sign = 1;
    }

    delete[] result;
    return res;
}

BigInt BigInt::operator*(int32_t x){
    return (*this) * BigInt(x);
}

bool BigInt::operator==(const BigInt &x){
    if (x.size != size || x.sign != sign){
        return false;
    }
    for(int i = size-1; i >= 0; i--){
        if (data[i] != x.data[i])
            return false;
    }
    return true;
}

bool BigInt::operator!=(const BigInt &x){
    return !(*this == x);
}

bool BigInt::operator>(const BigInt &x){
    if (sign != x.sign){
        return (sign < x.sign);
    }
    else if(size != x.size){
        if(sign == 0){
            return (size > x.size);
        }
        else{
            return (size < x.size);
        }
    }
    else{
        for(int i = size-1; i >= 0; i--){
            if (data[i] > x.data[i]){
                if(x.sign == 0){
                    return true;
                }
                else{
                    return false;
                }
            }
            else if (data[i] < x.data[i]){
                if(x.sign == 0){
                    return false;
                }
                else{
                    return true;
                }
            } 
        }
        return false;
    }
}

bool BigInt::operator<(const BigInt &x){
    return !(*this > x) && (*this != x);  
}

bool BigInt::operator<=(const BigInt &x){
    return !(*this > x);
}

bool BigInt::operator>=(const BigInt &x){
    return !(*this < x);
}

BigInt& BigInt::operator=(const BigInt &x){
    if(*this == x){
        return *this;
    }
    delete[] data;
    data = new char[x.size];
    std::copy(x.data, x.data + x.size, data);
    size = x.size;
    sign = x.sign;

    return *this;
}

std::ostream& operator<<(std::ostream &out, const BigInt &x){
    if (x.sign == 1){
        out << '-';
    }
    for(int i = x.size-1; i >= 0; i--){
        out << x.data[i];
    }

    return out;
}
BigInt::~BigInt(){
    delete[] data;
}
