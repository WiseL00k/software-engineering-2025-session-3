/**
 * @file Expression.h
 * @brief �����������ʽ�� Expression���������ɺͼ�������������ʽ��
 */

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include "Fraction.h"

 /**
  * @class Expression
  * @brief ��ʾһ������������ʽ���������������š����������
  */
class Expression {
private:
    std::string exprStr; ///< ���ʽ���ַ�����ʽ
    Fraction result;     ///< ���ʽ�ļ�����

public:
    /**
     * @brief ����һ���յı��ʽ
     */
    Expression() = default;

    /**
     * @brief ����һ�����ʽ
     * @param exp ���ʽ�ַ���
     */
    explicit Expression(const std::string& exp);

    /**
     * @brief ����һ���������������ʽ
     * @param range ��ֵ��Χ����10��ʾ0~9��
     * @param maxOps ������������
     */
    void generateRandom(int range, int maxOps = 3);

    /**
     * @brief ���㵱ǰ���ʽ��ֵ
     * @return ����õ��� Fraction ����
     */
    Fraction evaluate();

    /**
     * @brief ��ȡ���ʽ���ַ�����ʽ
     */
    std::string toString() const;

    /**
     * @brief ��ȡ���ʽ�Ľ��
     */
    Fraction getResult() const;
};

#endif // EXPRESSION_H
