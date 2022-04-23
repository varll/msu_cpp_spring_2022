#include <iostream>

class BigInt{
private:
    char *data;
    bool sign;
    size_t size;
    BigInt add(const BigInt &x, const BigInt &y);
    BigInt sub(const BigInt &x, const BigInt &y);

public:
    BigInt();
    BigInt(const BigInt &x);
    BigInt(int32_t x);
    BigInt(const std::string &x);
    BigInt operator+(const BigInt &x);
    BigInt operator-(const BigInt &x);
    BigInt operator+(const int32_t x);
    BigInt operator-();
    BigInt operator-(const int32_t x);
    BigInt operator*(const BigInt &x);
    BigInt operator*(const int32_t x);
    BigInt& operator=(const BigInt &x);
    bool operator==(const BigInt &x);
    bool operator!=(const BigInt &x);
    bool operator>(const BigInt &x);
    bool operator>=(const BigInt &x);
    bool operator<(const BigInt &x);
    bool operator<=(const BigInt &x);
    friend std::ostream& operator<<(std::ostream &out, const BigInt &x);
    ~BigInt();

    char* get_data(){
        return data;
    }
    bool get_sign(){
        return sign;
    }
    size_t get_size(){
        return size;
    }
};