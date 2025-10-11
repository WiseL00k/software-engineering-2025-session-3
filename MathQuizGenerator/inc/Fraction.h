/**
 * @file Fraction.h
 * @brief ��������� Fraction�����ڴ�������������������㡣
 */

#ifndef FRACTION_H
#define FRACTION_H

#include <string>

 /**
  * @class Fraction
  * @brief ��ʾһ���������������֧�ּӼ��˳������������
  */
class Fraction {
private:
    int numerator;   ///< ����
    int denominator; ///< ��ĸ��ʼ��Ϊ����

    /**
     * @brief �����������������Լ����GCD��
     * @param a ����
     * @param b ����
     * @return ���Լ��
     */
    static int gcd(int a, int b);

public:
    /**
     * @brief ����һ������
     * @param num ����
     * @param den ��ĸ����Ϊ0���׳��쳣��
     */
    Fraction(int num = 0, int den = 1);

    /**
     * @brief ��������Ϊ�����ʽ
     */
    void simplify();

    /**
     * @brief ���ؼӷ������
     * @param other ��һ������
     * @return ����������Ӻ�Ľ��
     */
    Fraction operator+(const Fraction& other) const;

    /**
     * @brief ���ؼ��������
     * @param other ��һ������
     * @return �������������Ľ������֤�Ǹ���
     */
    Fraction operator-(const Fraction& other) const;

    /**
     * @brief ���س˷������
     */
    Fraction operator*(const Fraction& other) const;

    /**
     * @brief ���س��������
     * @note ��������Ϊ0
     */
    Fraction operator/(const Fraction& other) const;

    /**
     * @brief ������ת��Ϊ�ַ�����ʽ
     * @return �ַ������� "3/5" �� "2'3/8"
     */
    std::string toString() const;

    /**
     * @brief ��ȡ�����ĸ���ֵ
     * @return double ���͵�С��ֵ
     */
    double toDouble() const;
};

#endif // FRACTION_H
