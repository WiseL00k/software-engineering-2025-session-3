#include "QuizGenerator.h"
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

void QuizGenerator::generateAll() {
    cout << "��ʼ���� " << numQuestions << " ����Ŀ..." << endl;

    quizzes.clear();
    set<string> existingExpressions;

    int attempts = 0;
    const int MAX_ATTEMPTS = numQuestions * 100;

    while (quizzes.size() < numQuestions && attempts < MAX_ATTEMPTS) {
        Expression expr;
        expr.generateRandom(range);

        string exprStr = expr.toString();

        if (existingExpressions.find(exprStr) == existingExpressions.end()) {
            try {
                Fraction result = expr.getResult();
                if (result.toDouble() >= 0) {
                    quizzes.push_back(expr);
                    existingExpressions.insert(exprStr);
                    cout << "������Ŀ " << quizzes.size() << ":" << exprStr << endl;
                }
            }
            catch (...) {
                // ��Ч���ʽ������
            }
        }
        attempts++;
    }

    cout << "��Ŀ������ɣ������� " << quizzes.size() << " ����Ŀ" << endl;
}


void QuizGenerator::saveExercises(const string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("�޷����ļ�: " + filename);
    }

    for (size_t i = 0; i < quizzes.size(); i++) {
        file << (i + 1) << ". " << quizzes[i].toString() << endl;
    }

    file.close();
    cout << "��Ŀ�ļ��ѱ��浽: " << filename << endl;
}

void QuizGenerator::saveAnswers(const string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("�޷����ļ�: " + filename);
    }

    for (size_t i = 0; i < quizzes.size(); i++) {
        file << (i + 1) << ". " << quizzes[i].getResult().toString() << endl;
    }

    file.close();
    cout << "���ļ��ѱ��浽: " << filename << endl;
}