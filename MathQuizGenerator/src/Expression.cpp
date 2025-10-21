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

// �� generateRandom �����У�ȷ��������Ч�ı��ʽ
void Expression::generateRandom(int range, int maxOps) {
    // �����
    vector<char> ops;
    ops.push_back('+');
    ops.push_back('-');
    ops.push_back('*');
    ops.push_back('/');

    int numOperators = Utils::randInt(maxOps) + 1;
    int numNumbers = numOperators + 1;

    vector<Fraction> numbers;
    vector<char> operators;

    // �������� - ȷ��������ֳ�0�����
    for (int i = 0; i < numNumbers; i++) {
        if (Utils::randInt(2) == 0) {
            // ���� - ����0�����ڲ����ʵ�λ��
            int num;
            do {
                num = Utils::randInt(range);
            } while (num == 0 && i > 0); // ����������0
            numbers.push_back(Fraction(num, 1));
        }
        else {
            // ����
            int denom = Utils::randInt(range - 2) + 2;
            if (denom < 2) denom = 2;
            int numer = Utils::randInt(denom - 1) + 1;
            numbers.push_back(Fraction(numer, denom));
        }
    }

    // ��������� - ���ⲻ�������������
    for (int i = 0; i < numOperators; i++) {
        int opIndex;
        // ����ǳ�����ȷ����һ�����ֲ���0
        if (i < numOperators - 1 && operators.size() > 0 && operators.back() == '/') {
            // ���������������¸��ӷ���
            opIndex = Utils::randInt(2); // ֻѡ�� + �� -
        }
        else {
            opIndex = Utils::randInt(ops.size());
        }
        operators.push_back(ops[static_cast<size_t>(opIndex)]);
    }

    // �����򵥱��ʽ�������ţ�
    stringstream ss;
    for (int i = 0; i < numNumbers; i++) {
        ss << numbers[static_cast<size_t>(i)].toString();
        if (i < numOperators) {
            ss << " " << operators[static_cast<size_t>(i)] << " ";
        }
    }

    exprStr = ss.str();

    // ��֤���ʽ
    int attempts = 0;
    while (attempts < 5) {
        try {
            result = evaluate();
            // �ſ����ƣ�ֻȷ������Ǹ�
            if (result.toDouble() >= 0) {
                break;
            }
        }
        catch (const exception& e) {
            // ��������
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

    // Ԥ����ȷ���������Χ�пո񣬱��ڽ���
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
                opStack.pop(); // ���� '('
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
            // ����δ֪�ַ�
            i++;
        }
    }

    while (!opStack.empty()) {
        performOperation(numStack, opStack);
    }

    if (numStack.size() != 1) {
        throw runtime_error("���ʽ�������");
    }

    return numStack.top();
}

// ����������ִ������
void Expression::performOperation(stack<Fraction>& numStack, stack<char>& opStack) {
    if (numStack.size() < 2 || opStack.empty()) {
        throw runtime_error("���ʽ��ʽ����");
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
        // ����������Ƿ�Ϊ��
        if ((a - b).toDouble() < 0) {
            throw runtime_error("�����������Ϊ����");
        }
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        // ����������Ƿ�Ϊ�����
        result = a / b;
        if (abs(result.getNumerator()) >= result.getDenominator() && result.getDenominator() != 1) {
            throw runtime_error("�����������Ϊ�����");
        }
        break;
    default:
        throw runtime_error("δ֪�����: " + string(1, op));
    }

    numStack.push(result);
}

// ������������ȡ��������ȼ�
int Expression::getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// �������������������ַ���
Fraction Expression::parseFraction(const string& str) {
    size_t apostrophePos = str.find('\'');
    size_t slashPos = str.find('/');

    if (apostrophePos != string::npos) {
        // ������
        int whole = stoi(str.substr(0, apostrophePos));
        string fracPart = str.substr(apostrophePos + 1);
        slashPos = fracPart.find('/');
        int numer = stoi(fracPart.substr(0, slashPos));
        int denom = stoi(fracPart.substr(slashPos + 1));
        return Fraction(whole * denom + numer, denom);
    }
    else if (slashPos != string::npos) {
        // �����
        int numer = stoi(str.substr(0, slashPos));
        int denom = stoi(str.substr(slashPos + 1));
        return Fraction(numer, denom);
    }
    else {
        // ����
        return Fraction(stoi(str), 1);
    }
}
/*
string Expression::toString() const {
    // �� * �� / ת���� �� �� �� ������ʾ
    string displayStr = exprStr;
    size_t pos = 0;
    while ((pos = displayStr.find('*', pos)) != string::npos) {
        displayStr.replace(pos, 1, "��");
        pos += 2; // �� ռ��2���ֽ�
    }
    pos = 0;
    while ((pos = displayStr.find('/', pos)) != string::npos) {
        displayStr.replace(pos, 1, "��");
        pos += 2; // �� ռ��2���ֽ�
    }
    return displayStr + " = ";
}
*/
string Expression::toString() const {
    // ֻ��Ҫת��������������Ѿ���ȷ��ʾ
    string displayStr = exprStr;

    // �������õ������ת��Ϊ��ʾ�õ������
    size_t pos = 0;
    while ((pos = displayStr.find('*', pos)) != string::npos) {
        displayStr.replace(pos, 1, "��");
        pos += 2;
    }

    pos = 0;
    while ((pos = displayStr.find('/', pos)) != string::npos) {
        // ������ / �Ƿ�������������Ƿ�����һ���֣�
        bool isOperator = true;

        // ����Ƿ�����һ���֣�ǰ�󶼻�������
        if (pos > 0 && pos + 1 < displayStr.length()) {
            if (isdigit(displayStr[pos - 1]) && isdigit(displayStr[pos + 1])) {
                isOperator = false;
            }
        }

        if (isOperator) {
            displayStr.replace(pos, 1, "��");
            pos += 2;
        }
        else {
            pos++; // ���������е�б��
        }
    }

    return displayStr + " = ";
}

Fraction Expression::getResult() const {
    return result;
}

std::string Expression::convertDisplayToCalculation(const std::string& displayStr) {
    std::string calcStr = displayStr;

    // �滻���� �� Ϊ *
    size_t pos = 0;
    while ((pos = calcStr.find('��', pos)) != std::string::npos) {
        calcStr.replace(pos, 1, "*");
        pos += 1; // ֻ��Ҫǰ��1λ����Ϊ�滻�󳤶Ȳ���
    }

    // �滻���� �� Ϊ /
    pos = 0;
    while ((pos = calcStr.find('��', pos)) != std::string::npos) {
        calcStr.replace(pos, 1, "/");
        pos += 1;
    }

    return calcStr;
}