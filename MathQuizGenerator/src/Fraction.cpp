#include "Fraction.h"
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <limits>

using namespace std;

int Fraction::gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

Fraction::Fraction(int num, int den) : numerator(num), denominator(den) {
    if (denominator == 0) {
        throw runtime_error("分母不能为零");
    }

    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    simplify();
}

void Fraction::simplify() {
    if (numerator == 0) {
        denominator = 1;
        return;
    }

    int common = gcd(numerator, denominator);
    numerator /= common;
    denominator /= common;

    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

Fraction Fraction::operator+(const Fraction& other) const {
    int newNum = numerator * other.denominator + other.numerator * denominator;
    int newDen = denominator * other.denominator;
    return Fraction(newNum, newDen);
}

Fraction Fraction::operator-(const Fraction& other) const {
    int newNum = numerator * other.denominator - other.numerator * denominator;
    int newDen = denominator * other.denominator;
    Fraction result(newNum, newDen);

    // 确保结果非负
    if (result.toDouble() < 0) {
        throw runtime_error("减法结果不能为负数");
    }

    return result;
}

Fraction Fraction::operator*(const Fraction& other) const {
    int newNum = numerator * other.numerator;
    int newDen = denominator * other.denominator;
    return Fraction(newNum, newDen);
}

Fraction Fraction::operator/(const Fraction& other) const {
    if (other.numerator == 0) {
        throw runtime_error("除数不能为零");
    }

    int newNum = numerator * other.denominator;
    int newDen = denominator * other.numerator;

    Fraction result(newNum, newDen);

    // 放宽限制：允许任何有效分数结果，不强制要求真分数
    // 因为复杂的表达式可能产生假分数
    return result;
}

string Fraction::toString() const {
    if (denominator == 1) {
        return to_string(numerator);
    }

    if (abs(numerator) < denominator) {
        // 真分数 - 显示为 1/2
        return to_string(numerator) + "/" + to_string(denominator);
    }
    else {
        // 带分数 - 显示为 1'1/2
        int whole = numerator / denominator;
        int remainder = abs(numerator % denominator);
        if (remainder == 0) {
            return to_string(whole);
        }
        return to_string(whole) + "'" + to_string(remainder) + "/" + to_string(denominator);
    }
}
double Fraction::toDouble() const {
    return static_cast<double>(numerator) / denominator;
}

