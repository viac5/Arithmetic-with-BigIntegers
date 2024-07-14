#pragma once
#include <iostream>
#include <string>
#include <cmath>

class BigInteger {
private:
    std::string value;
    size_t size;
public:
    BigInteger(std::string a = "0") : value(a), size(a.size()) {}

    std::string getValue();
    void setValue(std::string numb);

    BigInteger& operator=(const std::string& right); 
    BigInteger operator+(const BigInteger& other) const;
    BigInteger operator-(const BigInteger & other) const;
    BigInteger operator*(const BigInteger& other) const;
    BigInteger operator/(const BigInteger& other) const;
    BigInteger operator~() const;//квадратный корень
    BigInteger operator!() const;//факториал

    bool operator>(const BigInteger& other) const;
    bool operator>=(const BigInteger& other) const;
    bool operator<(const BigInteger& other) const;
    bool operator<=(const BigInteger& other) const;
    bool operator==(const BigInteger& other) const;
    bool operator!=(const BigInteger& other) const;
};
