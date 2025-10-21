/**
 * @file Expression.h
 * @brief 定义算术表达式类 Expression，用于生成和计算四则运算表达式。
 */

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <stack>
#include "Fraction.h"

 /**
  * @class Expression
  * @brief 表示一个四则运算表达式（包含分数、括号、运算符）。
  */
class Expression {
private:
    std::string exprStr; ///< 表达式的字符串形式
    Fraction result;     ///< 表达式的计算结果


    // 在 Expression.h 的 private 部分添加：
    /**
     * @brief 执行运算操作
     */
    static void performOperation(std::stack<Fraction>& numStack, std::stack<char>& opStack);

    /**
     * @brief 获取运算符优先级
     */
    static int getPrecedence(char op);

    /**
     * @brief 解析分数字符串
     */
    static Fraction parseFraction(const std::string& str);
public:
    /**
     * @brief 构造一个空的表达式
     */
    Expression() = default;

    /**
     * @brief 构造一个表达式
     * @param exp 表达式字符串
     */
    explicit Expression(const std::string& exp);

    /**
     * @brief 生成一个随机四则运算表达式
     * @param range 数值范围（如10表示0~9）
     * @param maxOps 最大运算符数量
     */
    void generateRandom(int range, int maxOps = 3);

    /**
     * @brief 计算当前表达式的值
     * @return 计算得到的 Fraction 对象
     */
    Fraction evaluate();

    /**
     * @brief 获取表达式的字符串形式
     */
    std::string toString() const;

    /**
     * @brief 获取表达式的结果
     */
    Fraction getResult() const;

    /**
     * @brief 将字符串表达式转化为程序可识别表达式
     */
    std::string convertDisplayToCalculation(const std::string& displayStr);
};

#endif // EXPRESSION_H
