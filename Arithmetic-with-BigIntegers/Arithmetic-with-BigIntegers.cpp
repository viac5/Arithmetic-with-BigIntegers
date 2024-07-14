#include "Arithmetic-with-BigIntegers.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

string BigInteger::getValue() {
    string value1 = this->value;
    return value1;
}
void BigInteger::setValue(string numb) {
    this->value=numb;
}

BigInteger& BigInteger::operator=(const std::string& right) {
    this->value = right;
    this->size = right.size();
    return *this;
}

BigInteger BigInteger::operator+(const BigInteger& other) const {
    std::string num1 = this->value;
    std::string num2 = other.value;
    std::string sum = "";
    bool lend = false;
    num1.insert(num1.begin(), '0');
    while (num2.size() < num1.size())
        num2.insert(num2.begin(), '0');
    while (num1.size() < num2.size())
        num1.insert(num1.begin(), '0');
    for (int i = num1.size() - 1; i >= 0; i--) {
        int ai = num1[i] - '0';
        int bi = num2[i] - '0';
        if (lend) {
            ai++;
            lend = false;
        }
        if (ai + bi < 10)
            sum.insert(sum.begin(), ai + bi + '0');
        else {
            ai -= 10;
            lend = true;
            sum.insert(sum.begin(), ai + bi + '0');
        }
    }
    if (sum[0] == '0')
        sum.erase(sum.begin());
    return sum;
    

    return BigInteger(sum);
}

BigInteger BigInteger::operator-(const BigInteger& other) const {
    std::string num1 = this->value;
    std::string num2 = other.value;
    std::string difference = "";

    bool borrow = false;
    while (num2.size() < num1.size())
        num2.insert(num2.begin(), '0');
    for (int j = num1.size() - 1; j >= 0; j--) {
        int ai = num1[j] - '0';
        int bi = num2[j] - '0';

        if (borrow) {
            ai--;
            borrow = false;
        }

        if (ai >= bi) {
            difference.insert(difference.begin(), ai - bi + '0');
        }
        else {
            ai += 10;
            borrow = true;
            difference.insert(difference.begin(), ai - bi + '0');
        }
    }

    while (difference.size() > 1 && difference[0] == '0') {
        difference.erase(difference.begin());
    }
    return BigInteger(difference);
}

BigInteger BigInteger::operator*(const BigInteger& other) const {

    std::string num1 = this->value;
    std::string num2 = other.value;
    BigInteger a, b;
    string numbA, numbB, res, prom;
    bool lend = false;
    if (num1.size() > num2.size()) {
        numbA = num1;
        numbB = num2;
    }
    else {
        numbA = num2;
        numbB = num1;
    }
    numbA.insert(numbA.begin(), '0');
    while (numbB.size() < numbA.size())
        numbB.insert(numbB.begin(), '0');
    int temp;

    for (int i = numbA.size() - 1; i >= 0; i--) {
        for (int j = numbA.size() - 1; j >= 0; j--) {
            int an = numbA[j] - '0';
            int bn = numbB[i] - '0';
            int ab = an * bn;
            if (lend) {
                ab += temp;
                lend = false;
            }
            if (ab < 10)
                prom.insert(prom.begin(), ab + '0');
            else {
                temp = ab / 10;
                lend = true;
                prom.insert(prom.begin(), ab % 10 + '0');
            }
        }
        for (int k = 0; k < numbA.size() - i - 1; k++) {
            prom.push_back('0');
        }
        a.setValue(res);
        b.setValue(prom);
        res = (a + b).getValue();
        prom = "";
    }
    while (res.size() > 1 && res[0] == '0') {
        res.erase(res.begin());
    }
    return res == "" ? BigInteger("0") : BigInteger(res);
    return BigInteger(res);
}

BigInteger BigInteger::operator/(const BigInteger& other) const {
    std::string a = this->value;
    std::string b = other.value;
    BigInteger num1, num2;
    if (a == "0" || b == "0")
        return  BigInteger("0");
    if (b == "1")
        return  BigInteger(a);
    if (a.size() < b.size())
        return  BigInteger("0");

    string quotient, prom;
    int k = 0;
    num1.setValue(prom);
    num2.setValue(b);
    while (num1 < num2 && k < a.size()) {
        prom.push_back(a[k]);
        num1.setValue(prom);
        k++;
    }
    // Делим в столбик
    num1.setValue(prom);
    while (k <= a.size()) {
        int discrete = 0;
        while (num1 >= num2) {
            prom = (num1-num2).getValue();
            num1.setValue(prom);
            discrete++;
        }
        quotient += to_string(discrete);
        if (k < a.size()) {
            prom.push_back(a[k]);
            num1.setValue(prom);
            k++;
        }
        else {
            break;
        }
    }
    while (prom.size() > 1 && prom[0] == '0') {
        prom.erase(prom.begin());
    }

    return BigInteger(quotient);
}

BigInteger BigInteger::operator~ /*квадратный корень*/() const {
    string x0, n=this->value;
    BigInteger a, b, c, d("2");
    long long sq = 0;
    int even = 0;
    if (n.size() % 2 == 0)
        even = 1;
    if (n.size() >= 16) {
        for (int i = 0; i < 8 + even; i++)
            sq += (n[i] - 48) * pow(10, 8 + even - i);

        int s = sqrt(sq);
        x0 = to_string(s);
        for (int i = x0.size(); i < (n.size() / 2) + (n.size() % 2); i++)
            x0 += "0";
        // Метод Ньютона
        bool decreased = false;
        for (;;) {
            a.setValue(x0);
            b.setValue(n);
            string xn = ((a+(b/a))/ d).getValue();
            c.setValue(xn);
            if (x0 == xn || c > a == 1 && decreased)
                break;
            decreased = c < a;
            x0 = xn;
            a.setValue(x0);
        }
        return BigInteger(x0);
    }
    if (n.size() < 16) {
        for (int i = 0; i < n.size(); i++)
            sq += (n[i] - 48) * pow(10, n.size() - 1 - i);
        int s = sqrt(sq);
        x0 = to_string(s);
        return BigInteger(x0);
    }
}

BigInteger BigInteger::operator! /*факториал*/() const {
    string numb = this->value;
    int factorial = 0, Size = this->size;
    BigInteger a("1"), b;
    for (int i = 0; i < Size; i++)
    {
        factorial += (numb[i]-48) * pow(10,Size - i-1);
    }
    if (factorial <= 0)
        return BigInteger("0");
    string res = "1";
    for (int i = 2; i < factorial + 1; i++) {
        b.setValue(to_string(i));
        res = (a*b).getValue();
        a.setValue(res);
    }
    return BigInteger(res);
}


bool BigInteger::operator>(const BigInteger& other) const {
    std::string numbA = this->value;
    std::string numbB = other.value;
    while (numbA.size() > 1 && numbA[0] == '0') {
        numbA.erase(numbA.begin());
    }
    while (numbB.size() > 1 && numbB[0] == '0') {
        numbB.erase(numbB.begin());
    }
    if (numbA.size() == numbB.size()) {
        for (int i = 0; i < numbA.size(); i++) {
            if (numbA[i] > numbB[i])
                return true;
            if (numbA[i] < numbB[i])
                return false;
        }
        return false;
    }
    return numbA.size() > numbB.size() ? true : false;
}

bool BigInteger::operator>=(const BigInteger& other) const {
    std::string numbA = this->value;
    std::string numbB = other.value;
    while (numbA.size() > 1 && numbA[0] == '0') {
        numbA.erase(numbA.begin());
    }
    while (numbB.size() > 1 && numbB[0] == '0') {
        numbB.erase(numbB.begin());
    }
    if (numbA.size() == numbB.size()) {
        for (int i = 0; i < numbA.size(); i++) {
            if (numbA[i] > numbB[i])
                return true;
            if (numbA[i] < numbB[i])
                return false;
        }
        return true;
    }
    return numbA.size() > numbB.size() ? true : false;
}

bool BigInteger::operator<(const BigInteger& other) const {
    std::string numbA = this->value;
    std::string numbB = other.value;
    while (numbA.size() > 1 && numbA[0] == '0') {
        numbA.erase(numbA.begin());
    }
    while (numbB.size() > 1 && numbB[0] == '0') {
        numbB.erase(numbB.begin());
    }
    if (numbA.size() == numbB.size()) {
        for (int i = 0; i < numbA.size(); i++) {
            if (numbA[i] > numbB[i])
                return false;
            if (numbA[i] < numbB[i])
                return true;
        }
        return false;
    }
    return numbA.size() > numbB.size() ? false : true;
}

bool BigInteger::operator<=(const BigInteger& other) const {
    std::string numbA = this->value;
    std::string numbB = other.value;
    while (numbA.size() > 1 && numbA[0] == '0') {
        numbA.erase(numbA.begin());
    }
    while (numbB.size() > 1 && numbB[0] == '0') {
        numbB.erase(numbB.begin());
    }
    if (numbA.size() == numbB.size()) {
        for (int i = 0; i < numbA.size(); i++) {
            if (numbA[i] > numbB[i])
                return false;
            if (numbA[i] < numbB[i])
                return true;
        }
        return true;
    }
    return numbA.size() > numbB.size() ? false : true;
}

bool BigInteger::operator==(const BigInteger& other) const {
    std::string numbA = this->value;
    std::string numbB = other.value;
    while (numbA.size() > 1 && numbA[0] == '0') {
        numbA.erase(numbA.begin());
    }
    while (numbB.size() > 1 && numbB[0] == '0') {
        numbB.erase(numbB.begin());
    }
    if (numbA.size() == numbB.size()) {
        for (int i = 0; i < numbA.size(); i++) {
            if (numbA[i] > numbB[i])
                return false;
            if (numbA[i] < numbB[i])
                return false;
        }
        return true;
    }
    return numbA.size() > numbB.size() ? false : false;
}

bool BigInteger::operator!=(const BigInteger& other) const {
    std::string numbA = this->value;
    std::string numbB = other.value;
    while (numbA.size() > 1 && numbA[0] == '0') {
        numbA.erase(numbA.begin());
    }
    while (numbB.size() > 1 && numbB[0] == '0') {
        numbB.erase(numbB.begin());
    }
    if (numbA.size() == numbB.size()) {
        for (int i = 0; i < numbA.size(); i++) {
            if (numbA[i] > numbB[i])
                return true;
            if (numbA[i] < numbB[i])
                return true;
        }
        return false;
    }
    return numbA.size() > numbB.size() ? true : true;
}

