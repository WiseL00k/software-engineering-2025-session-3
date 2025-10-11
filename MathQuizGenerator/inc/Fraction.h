/**
 * @file Fraction.h
 * @brief 定义分数类 Fraction，用于处理真分数及其四则运算。
 */

#ifndef FRACTION_H
#define FRACTION_H

#include <string>

 /**
  * @class Fraction
  * @brief 表示一个真分数或整数，支持加减乘除及化简操作。
  */
class Fraction {
private:
    int numerator;   ///< 分子
    int denominator; ///< 分母，始终为正数

    /**
     * @brief 计算两个整数的最大公约数（GCD）
     * @param a 整数
     * @param b 整数
     * @return 最大公约数
     */
    static int gcd(int a, int b);

public:
    /**
     * @brief 构造一个分数
     * @param num 分子
     * @param den 分母（若为0将抛出异常）
     */
    Fraction(int num = 0, int den = 1);

    /**
     * @brief 将分数化为最简形式
     */
    void simplify();

    /**
     * @brief 重载加法运算符
     * @param other 另一个分数
     * @return 两个分数相加后的结果
     */
    Fraction operator+(const Fraction& other) const;

    /**
     * @brief 重载减法运算符
     * @param other 另一个分数
     * @return 两个分数相减后的结果（保证非负）
     */
    Fraction operator-(const Fraction& other) const;

    /**
     * @brief 重载乘法运算符
     */
    Fraction operator*(const Fraction& other) const;

    /**
     * @brief 重载除法运算符
     * @note 除数不能为0
     */
    Fraction operator/(const Fraction& other) const;

    /**
     * @brief 将分数转换为字符串格式
     * @return 字符串，如 "3/5" 或 "2'3/8"
     */
    std::string toString() const;

    /**
     * @brief 获取分数的浮点值
     * @return double 类型的小数值
     */
    double toDouble() const;
};

#endif // FRACTION_H
