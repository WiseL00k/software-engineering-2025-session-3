#include "AnswerChecker.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Fraction.h"
#include "Utils.h"

using namespace std;

// 辅助函数：提取纯答案内容（去除题号）
string extractPureAnswer(const string& answerLine) {
    string answer = answerLine;

    // 去除首尾空格
    answer.erase(0, answer.find_first_not_of(" "));
    answer.erase(answer.find_last_not_of(" ") + 1);

    // 查找题号结束位置（第一个点号后的内容）
    size_t dotPos = answer.find('.');
    if (dotPos != string::npos) {
        // 找到点号，取点号后面的内容
        answer = answer.substr(dotPos + 1);
        // 再次去除空格
        answer.erase(0, answer.find_first_not_of(" "));
        answer.erase(answer.find_last_not_of(" ") + 1);
    }

    return answer;
}

// 辅助函数：比较两个答案是否相等
bool compareAnswers(const string& userAnswer, const string& correctAnswer) {
    string userAns = userAnswer;
    string correctAns = correctAnswer;

    // 去除所有空格
    userAns.erase(remove(userAns.begin(), userAns.end(), ' '), userAns.end());
    correctAns.erase(remove(correctAns.begin(), correctAns.end(), ' '), correctAns.end());

    // 直接比较字符串
    if (userAns == correctAns) {
        return true;
    }

    // 如果字符串不相等，尝试解析为分数进行比较
    try {
        Fraction userFrac, correctFrac;

        // 解析用户答案
        if (userAns.find('/') != string::npos) {
            if (userAns.find('\'') != string::npos) {
                // 带分数
                size_t apostrophePos = userAns.find('\'');
                int whole = stoi(userAns.substr(0, apostrophePos));
                string fracPart = userAns.substr(apostrophePos + 1);
                size_t slashPos = fracPart.find('/');
                int numer = stoi(fracPart.substr(0, slashPos));
                int denom = stoi(fracPart.substr(slashPos + 1));
                userFrac = Fraction(whole * denom + numer, denom);
            }
            else {
                // 真分数
                size_t slashPos = userAns.find('/');
                int numer = stoi(userAns.substr(0, slashPos));
                int denom = stoi(userAns.substr(slashPos + 1));
                userFrac = Fraction(numer, denom);
            }
        }
        else {
            // 整数
            userFrac = Fraction(stoi(userAns), 1);
        }

        // 解析正确答案
        if (correctAns.find('/') != string::npos) {
            if (correctAns.find('\'') != string::npos) {
                size_t apostrophePos = correctAns.find('\'');
                int whole = stoi(correctAns.substr(0, apostrophePos));
                string fracPart = correctAns.substr(apostrophePos + 1);
                size_t slashPos = fracPart.find('/');
                int numer = stoi(fracPart.substr(0, slashPos));
                int denom = stoi(fracPart.substr(slashPos + 1));
                correctFrac = Fraction(whole * denom + numer, denom);
            }
            else {
                size_t slashPos = correctAns.find('/');
                int numer = stoi(correctAns.substr(0, slashPos));
                int denom = stoi(correctAns.substr(slashPos + 1));
                correctFrac = Fraction(numer, denom);
            }
        }
        else {
            correctFrac = Fraction(stoi(correctAns), 1);
        }

        // 比较两个分数（简化后比较）
        userFrac.simplify();
        correctFrac.simplify();
        return userFrac.getNumerator() == correctFrac.getNumerator() &&
            userFrac.getDenominator() == correctFrac.getDenominator();

    }
    catch (...) {
        return false;
    }
}

void AnswerChecker::checkAnswers(const string& exerciseFile, const string& answerFile, const string& outputFile) {
    // 实际上我们只需要用户答案文件，标准答案固定为 Answers.txt
    ifstream userAnsFile(answerFile);        // 用户答案文件
    ofstream outFile(outputFile);

    if (!userAnsFile.is_open()) {
        throw runtime_error("无法打开用户答案文件: " + answerFile);
    }
    if (!outFile.is_open()) {
        throw runtime_error("无法打开输出文件: " + outputFile);
    }

    // 标准答案文件固定为 Answers.txt
    ifstream correctAnsFile("Answers.txt");
    if (!correctAnsFile.is_open()) {
        throw runtime_error("无法打开标准答案文件: Answers.txt");
    }

    vector<int> correctIndices, wrongIndices;
    string correctAnswerLine, userAnswerLine;
    int index = 1;

    cout << "正在批改答案..." << endl;
    cout << "标准答案文件: Answers.txt" << endl;
    cout << "用户答案文件: " << answerFile << endl;

    // 同时读取标准答案文件和用户答案文件
    while (getline(correctAnsFile, correctAnswerLine) && getline(userAnsFile, userAnswerLine)) {
        // 提取纯答案内容（去除题号）
        string correctAnswer = extractPureAnswer(correctAnswerLine);
        string userAnswer = extractPureAnswer(userAnswerLine);

        // 比较答案
        if (compareAnswers(userAnswer, correctAnswer)) {
            correctIndices.push_back(index);
        }
        else {
            wrongIndices.push_back(index);
        }

        index++;
    }

    // 输出结果（保持现有格式）
    cout << "Correct: " << correctIndices.size();
    if (!correctIndices.empty()) {
        cout << " (";
        for (size_t i = 0; i < correctIndices.size(); i++) {
            cout << correctIndices[i];
            if (i != correctIndices.size() - 1) cout << ", ";
        }
        cout << ")";
    }
    cout << endl;

    cout << "Wrong: " << wrongIndices.size();
    if (!wrongIndices.empty()) {
        cout << " (";
        for (size_t i = 0; i < wrongIndices.size(); i++) {
            cout << wrongIndices[i];
            if (i != wrongIndices.size() - 1) cout << ", ";
        }
        cout << ")";
    }
    cout << endl;

    // 保存到文件
    outFile << "Correct: " << correctIndices.size();
    if (!correctIndices.empty()) {
        outFile << " (";
        for (size_t i = 0; i < correctIndices.size(); i++) {
            outFile << correctIndices[i];
            if (i != correctIndices.size() - 1) outFile << ", ";
        }
        outFile << ")";
    }
    outFile << endl;

    outFile << "Wrong: " << wrongIndices.size();
    if (!wrongIndices.empty()) {
        outFile << " (";
        for (size_t i = 0; i < wrongIndices.size(); i++) {
            outFile << wrongIndices[i];
            if (i != wrongIndices.size() - 1) outFile << ", ";
        }
        outFile << ")";
    }
    outFile << endl;

    correctAnsFile.close();
    userAnsFile.close();
    outFile.close();

    cout << "结果已保存到: " << outputFile << endl;
}