#include "AnswerChecker.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Fraction.h"
#include "Utils.h"

using namespace std;

// ������������ȡ�������ݣ�ȥ����ţ�
string extractPureAnswer(const string& answerLine) {
    string answer = answerLine;

    // ȥ����β�ո�
    answer.erase(0, answer.find_first_not_of(" "));
    answer.erase(answer.find_last_not_of(" ") + 1);

    // ������Ž���λ�ã���һ����ź�����ݣ�
    size_t dotPos = answer.find('.');
    if (dotPos != string::npos) {
        // �ҵ���ţ�ȡ��ź��������
        answer = answer.substr(dotPos + 1);
        // �ٴ�ȥ���ո�
        answer.erase(0, answer.find_first_not_of(" "));
        answer.erase(answer.find_last_not_of(" ") + 1);
    }

    return answer;
}

// �����������Ƚ��������Ƿ����
bool compareAnswers(const string& userAnswer, const string& correctAnswer) {
    string userAns = userAnswer;
    string correctAns = correctAnswer;

    // ȥ�����пո�
    userAns.erase(remove(userAns.begin(), userAns.end(), ' '), userAns.end());
    correctAns.erase(remove(correctAns.begin(), correctAns.end(), ' '), correctAns.end());

    // ֱ�ӱȽ��ַ���
    if (userAns == correctAns) {
        return true;
    }

    // ����ַ�������ȣ����Խ���Ϊ�������бȽ�
    try {
        Fraction userFrac, correctFrac;

        // �����û���
        if (userAns.find('/') != string::npos) {
            if (userAns.find('\'') != string::npos) {
                // ������
                size_t apostrophePos = userAns.find('\'');
                int whole = stoi(userAns.substr(0, apostrophePos));
                string fracPart = userAns.substr(apostrophePos + 1);
                size_t slashPos = fracPart.find('/');
                int numer = stoi(fracPart.substr(0, slashPos));
                int denom = stoi(fracPart.substr(slashPos + 1));
                userFrac = Fraction(whole * denom + numer, denom);
            }
            else {
                // �����
                size_t slashPos = userAns.find('/');
                int numer = stoi(userAns.substr(0, slashPos));
                int denom = stoi(userAns.substr(slashPos + 1));
                userFrac = Fraction(numer, denom);
            }
        }
        else {
            // ����
            userFrac = Fraction(stoi(userAns), 1);
        }

        // ������ȷ��
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

        // �Ƚ������������򻯺�Ƚϣ�
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
    // ʵ��������ֻ��Ҫ�û����ļ�����׼�𰸹̶�Ϊ Answers.txt
    ifstream userAnsFile(answerFile);        // �û����ļ�
    ofstream outFile(outputFile);

    if (!userAnsFile.is_open()) {
        throw runtime_error("�޷����û����ļ�: " + answerFile);
    }
    if (!outFile.is_open()) {
        throw runtime_error("�޷�������ļ�: " + outputFile);
    }

    // ��׼���ļ��̶�Ϊ Answers.txt
    ifstream correctAnsFile("Answers.txt");
    if (!correctAnsFile.is_open()) {
        throw runtime_error("�޷��򿪱�׼���ļ�: Answers.txt");
    }

    vector<int> correctIndices, wrongIndices;
    string correctAnswerLine, userAnswerLine;
    int index = 1;

    cout << "�������Ĵ�..." << endl;
    cout << "��׼���ļ�: Answers.txt" << endl;
    cout << "�û����ļ�: " << answerFile << endl;

    // ͬʱ��ȡ��׼���ļ����û����ļ�
    while (getline(correctAnsFile, correctAnswerLine) && getline(userAnsFile, userAnswerLine)) {
        // ��ȡ�������ݣ�ȥ����ţ�
        string correctAnswer = extractPureAnswer(correctAnswerLine);
        string userAnswer = extractPureAnswer(userAnswerLine);

        // �Ƚϴ�
        if (compareAnswers(userAnswer, correctAnswer)) {
            correctIndices.push_back(index);
        }
        else {
            wrongIndices.push_back(index);
        }

        index++;
    }

    // ���������������и�ʽ��
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

    // ���浽�ļ�
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

    cout << "����ѱ��浽: " << outputFile << endl;
}