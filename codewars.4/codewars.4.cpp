#include <iostream>
#include <string>
#include <utility>
#include <cmath>
using namespace std;

string summation(string a, string b) {  // Сумма
    string sum;
    bool lend = false;
    a.insert(a.begin(), '0');
    while (b.size() < a.size()) b.insert(b.begin(), '0');
    while (a.size() < b.size()) a.insert(a.begin(), '0');
    for (int i = a.size() - 1; i >= 0; i--) {
        int ai = a[i] - '0';
        int bi = b[i] - '0';
        if (lend) {
            ai++;
            lend = false;
        }
        if (ai + bi < 10)sum.insert(sum.begin(), ai + bi + '0');
        else {
            ai -= 10;
            lend = true;
            sum.insert(sum.begin(), ai + bi + '0');
        }
    }
    if (sum[0] == '0')sum.erase(sum.begin());
    return sum;
 }

string subtraction(string a, string b) {  // Разность
    string difference;
    bool borrow = false;
    while (b.size() < a.size()) b.insert(b.begin(), '0');
    for (int j = a.size() - 1; j >= 0; j--) {
        int ai = a[j] - '0';
        int bi = b[j] - '0';

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

    return difference;
}

int Compare(string numbA, string numbB) {  // Сравнение
    while (numbA.size() > 1 && numbA[0] == '0') {
        numbA.erase(numbA.begin());
    }
    while (numbB.size() > 1 && numbB[0] == '0') {
        numbB.erase(numbB.begin());
    }
    if (numbA.size() == numbB.size()) {
        for (int i = 0; i < numbA.size(); i++) {
            if (numbA[i] > numbB[i]) return 1;
            if (numbA[i] < numbB[i]) return -1;
        }
        return 0;
    }
    return numbA.size() > numbB.size() ? 1 : -1;
}

string multiply(string a, string b) {  // Произведение
    string numbA, numbB,res,prom; 
    bool lend = false;
    if (a.size() > b.size()) { numbA = a; numbB = b; }
    else { numbA = b; numbB = a; }
    numbA.insert(numbA.begin(), '0');
    while (numbB.size() < numbA.size()) numbB.insert(numbB.begin(), '0');
    int temp;

    for (int i = numbA.size()-1; i >= 0; i--)
    {
        for (int j = numbA.size() - 1; j >= 0; j--)
        {
            int an = numbA[j] - '0';
            int bn = numbB[i] - '0';
            int ab = an * bn;
            if (lend) {
                ab += temp;
                lend = false;
            }
            if (ab < 10)prom.insert(prom.begin(), ab + '0');
            else {
                temp = ab/ 10;
                lend = true;
                prom.insert(prom.begin(), ab%10 + '0');
            }
        }
        for (int k = 0; k < numbA.size()-i-1; k++)
        {
            prom.push_back('0');
        }
        res = summation(res, prom);
        prom = "";
    }
    while (res.size() > 1 && res[0] == '0') {
        res.erase(res.begin());
    }
    return res=="" ? "0":res;
}

string divide_strings(const std::string& a, const std::string& b) {  // Частное
    if (a == "0" || b == "0") return "0";
    if (b == "1") return  a;
    if (a.size() < b.size()) return "0";

    string quotient, prom;
    int k = 0;

    while (Compare(prom, b) < 0 && k < a.size()) {
        prom.push_back(a[k]);
        k++;
    }
    // Делим в столбик
    while (k <= a.size()) {
        int discrete = 0;
        while (Compare(prom, b) >= 0) {
            prom = subtraction(prom, b);
            discrete++;
        }
        quotient += to_string(discrete);
        if (k < a.size()) {
            prom.push_back(a[k]);
            k++;
        }
        else {
            break;
        }
    }
    while (prom.size() > 1 && prom[0] == '0') {
        prom.erase(prom.begin());
    }

    return quotient;
}

string integer_square_root(string n) {  // Квадратный корень
    string x0;
    long long sq = 0;
    int even = 0;
    if (n.size() % 2 == 0)even = 1;
    if (n.size() >= 16) {
        for (int i = 0; i < 8+ even; i++)sq += (n[i]-48) * pow(10, 8+ even - i);
        
        int s = sqrt(sq);
        x0 = to_string(s);
        for (int i = x0.size(); i < (n.size() / 2)+(n.size() % 2); i++)x0 += "0";
        // Метод Ньютона
        bool decreased = false;
        for (;;) {
            string xn = divide_strings(summation(x0, divide_strings(n, x0)), "2");
            if (x0 == xn || Compare(xn, x0) == 1 && decreased) break;
            decreased = Compare(xn, x0) == -1;
            x0 = xn;
        }
        return x0;
    }
    if (n.size() < 16) {
        for (int i = 0; i < n.size(); i++)sq += (n[i] - 48) * pow(10, n.size() -1-i);
        int s = sqrt(sq);
        x0 = to_string(s);
        cout << x0;
        return x0;
    }
}

std::string factorial(int factorial) {  // Факториал
    if (factorial <= 0)return "";
    string res="1";
    for (int i = 2; i < factorial+1; i++)
    {
        res = multiply(res, to_string(i));
    }
    return res;
}


int main()
{
    cout << integer_square_root("654684984516164684546516451354649879746546498984984949898798798746546549879845664987984654654");
}
