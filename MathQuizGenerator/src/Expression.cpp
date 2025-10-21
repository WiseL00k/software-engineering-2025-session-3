#include "Expression.h"
#include "Utils.h"
#include <stack>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <algorithm>
#include <vector>

using namespace std;

Expression::Expression(const string& exp) : exprStr(convertDisplayToCalculation(exp)) {
    result = evaluate();
}

// 在 generateRandom 方法中，确保生成有效的表达式
void Expression::generateRandom(int range, int maxOps) {
    // 运算符
    vector<char> ops;
    ops.push_back('+');
    ops.push_back('-');
    ops.push_back('*');
    ops.push_back('/');

    int numOperators = Utils::randInt(maxOps) + 1;
    int numNumbers = numOperators + 1;

    vector<Fraction> numbers;
    vector<char> operators;

    // 生成数字 - 确保不会出现除0等情况
    for (int i = 0; i < numNumbers; i++) {
        if (Utils::randInt(2) == 0) {
            // 整数 - 避免0出现在不合适的位置
            int num;
            do {
                num = Utils::randInt(range);
            } while (num == 0 && i > 0); // 避免连续的0
            numbers.push_back(Fraction(num, 1));
        }
        else {
            // 分数
            int denom = Utils::randInt(range - 2) + 2;
            if (denom < 2) denom = 2;
            int numer = Utils::randInt(denom - 1) + 1;
            numbers.push_back(Fraction(numer, denom));
        }
    }

    // 生成运算符 - 避免不合理的运算符组合
    for (int i = 0; i < numOperators; i++) {
        int opIndex;
        // 如果是除法，确保下一个数字不是0
        if (i < numOperators - 1 && operators.size() > 0 && operators.back() == '/') {
            // 避免连续除法导致复杂分数
            opIndex = Utils::randInt(2); // 只选择 + 或 -
        }
        else {
            opIndex = Utils::randInt(ops.size());
        }
        operators.push_back(ops[static_cast<size_t>(opIndex)]);
    }

    // 构建简单表达式（无括号）
    stringstream ss;
    for (int i = 0; i < numNumbers; i++) {
        ss << numbers[static_cast<size_t>(i)].toString();
        if (i < numOperators) {
            ss << " " << operators[static_cast<size_t>(i)] << " ";
        }
    }

    exprStr = ss.str();

    // 验证表达式
    int attempts = 0;
    while (attempts < 5) {
        try {
            result = evaluate();
            // 放宽限制，只确保结果非负
            if (result.toDouble() >= 0) {
                break;
            }
        }
        catch (const exception& e) {
            // 重新生成
            numbers.clear();
            operators.clear();

            for (int i = 0; i < numNumbers; i++) {
                if (Utils::randInt(2) == 0) {
                    int num;
                    do {
                        num = Utils::randInt(range);
                    } while (num == 0 && i > 0);
                    numbers.push_back(Fraction(num, 1));
                }
                else {
                    int denom = Utils::randInt(range - 2) + 2;
                    if (denom < 2) denom = 2;
                    int numer = Utils::randInt(denom - 1) + 1;
                    numbers.push_back(Fraction(numer, denom));
                }
            }

            for (int i = 0; i < numOperators; i++) {
                int opIndex = Utils::randInt(ops.size());
                operators.push_back(ops[static_cast<size_t>(opIndex)]);
            }

            stringstream newSs;
            for (int i = 0; i < numNumbers; i++) {
                newSs << numbers[static_cast<size_t>(i)].toString();
                if (i < numOperators) {
                    newSs << " " << operators[static_cast<size_t>(i)] << " ";
                }
            }
            exprStr = newSs.str();
        }
        attempts++;
    }
}

Fraction Expression::evaluate() {
    stack<Fraction> numStack;
    stack<char> opStack;

    string expr = exprStr;

    // 预处理：确保运算符周围有空格，便于解析
    string processedExpr;
    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
            if (!processedExpr.empty() && processedExpr.back() != ' ') {
                processedExpr += ' ';
            }
            processedExpr += c;
            processedExpr += ' ';
        }
        else {
            processedExpr += c;
        }
    }

    expr = processedExpr;

    size_t i = 0;
    while (i < expr.length()) {
        if (expr[i] == ' ') {
            i++;
            continue;
        }

        if (expr[i] == '(') {
            opStack.push('(');
            i++;
        }
        else if (expr[i] == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                performOperation(numStack, opStack);
            }
            if (!opStack.empty()) {
                opStack.pop(); // 弹出 '('
            }
            i++;
        }
        else if (isdigit(static_cast<unsigned char>(expr[i])) || expr[i] == '\'') {
            string numStr;
            while (i < expr.length() &&
                (isdigit(static_cast<unsigned char>(expr[i])) ||
                    expr[i] == '/' || expr[i] == '\'')) {
                numStr += expr[i];
                i++;
            }

            Fraction num = parseFraction(numStr);
            numStack.push(num);
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            char currentOp = expr[i];

            while (!opStack.empty() && opStack.top() != '(' &&
                getPrecedence(opStack.top()) >= getPrecedence(currentOp)) {
                performOperation(numStack, opStack);
            }
            opStack.push(currentOp);
            i++;
        }
        else {
            // 跳过未知字符
            i++;
        }
    }

    while (!opStack.empty()) {
        performOperation(numStack, opStack);
    }

    if (numStack.size() != 1) {
        throw runtime_error("表达式计算错误");
    }

    return numStack.top();
}

// 辅助函数：执行运算
void Expression::performOperation(stack<Fraction>& numStack, stack<char>& opStack) {
    if (numStack.size() < 2 || opStack.empty()) {
        throw runtime_error("表达式格式错误");
    }

    char op = opStack.top();
    opStack.pop();

    Fraction b = numStack.top();
    numStack.pop();
    Fraction a = numStack.top();
    numStack.pop();

    Fraction result;
    switch (op) {
    case '+':
        result = a + b;
        break;
    case '-':
        // 检查减法结果是否为负
        if ((a - b).toDouble() < 0) {
            throw runtime_error("减法结果不能为负数");
        }
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        // 检查除法结果是否为真分数
        result = a / b;
        if (abs(result.getNumerator()) >= result.getDenominator() && result.getDenominator() != 1) {
            throw runtime_error("除法结果必须为真分数");
        }
        break;
    default:
        throw runtime_error("未知运算符: " + string(1, op));
    }

    numStack.push(result);
}

// 辅助函数：获取运算符优先级
int Expression::getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 辅助函数：解析分数字符串
Fraction Expression::parseFraction(const string& str) {
    size_t apostrophePos = str.find('\'');
    size_t slashPos = str.find('/');

    if (apostrophePos != string::npos) {
        // 带分数
        int whole = stoi(str.substr(0, apostrophePos));
        string fracPart = str.substr(apostrophePos + 1);
        slashPos = fracPart.find('/');
        int numer = stoi(fracPart.substr(0, slashPos));
        int denom = stoi(fracPart.substr(slashPos + 1));
        return Fraction(whole * denom + numer, denom);
    }
    else if (slashPos != string::npos) {
        // 真分数
        int numer = stoi(str.substr(0, slashPos));
        int denom = stoi(str.substr(slashPos + 1));
        return Fraction(numer, denom);
    }
    else {
        // 整数
        return Fraction(stoi(str), 1);
    }
}
/*
string Expression::toString() const {
    // 将 * 和 / 转换回 × 和 ÷ 用于显示
    string displayStr = exprStr;
    size_t pos = 0;
    while ((pos = displayStr.find('*', pos)) != string::npos) {
        displayStr.replace(pos, 1, "×");
        pos += 2; // × 占用2个字节
    }
    pos = 0;
    while ((pos = displayStr.find('/', pos)) != string::npos) {
        displayStr.replace(pos, 1, "÷");
        pos += 2; // ÷ 占用2个字节
    }
    return displayStr + " = ";
}
*/
string Expression::toString() const {
    // 只需要转换运算符，分数已经正确显示
    string displayStr = exprStr;

    // 将计算用的运算符转换为显示用的运算符
    size_t pos = 0;
    while ((pos = displayStr.find('*', pos)) != string::npos) {
        displayStr.replace(pos, 1, "×");
        pos += 2;
    }

    pos = 0;
    while ((pos = displayStr.find('/', pos)) != string::npos) {
        // 检查这个 / 是否是运算符（不是分数的一部分）
        bool isOperator = true;

        // 如果是分数的一部分，前后都会有数字
        if (pos > 0 && pos + 1 < displayStr.length()) {
            if (isdigit(displayStr[pos - 1]) && isdigit(displayStr[pos + 1])) {
                isOperator = false;
            }
        }

        if (isOperator) {
            displayStr.replace(pos, 1, "÷");
            pos += 2;
        }
        else {
            pos++; // 跳过分数中的斜杠
        }
    }

    return displayStr + " = ";
}

Fraction Expression::getResult() const {
    return result;
}

std::string Expression::convertDisplayToCalculation(const std::string& displayStr) {
    std::string calcStr = displayStr;

    // 替换所有 × 为 *
    size_t pos = 0;
    while ((pos = calcStr.find('×', pos)) != std::string::npos) {
        calcStr.replace(pos, 1, "*");
        pos += 1; // 只需要前进1位，因为替换后长度不变
    }

    // 替换所有 ÷ 为 /
    pos = 0;
    while ((pos = calcStr.find('÷', pos)) != std::string::npos) {
        calcStr.replace(pos, 1, "/");
        pos += 1;
    }

    return calcStr;
}