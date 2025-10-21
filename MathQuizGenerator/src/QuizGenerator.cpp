#include "QuizGenerator.h"
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

void QuizGenerator::generateAll() {
    cout << "开始生成 " << numQuestions << " 道题目..." << endl;

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
                    cout << "生成题目 " << quizzes.size() << ":" << exprStr << endl;
                }
            }
            catch (...) {
                // 无效表达式，跳过
            }
        }
        attempts++;
    }

    cout << "题目生成完成，共生成 " << quizzes.size() << " 道题目" << endl;
}


void QuizGenerator::saveExercises(const string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("无法打开文件: " + filename);
    }

    for (size_t i = 0; i < quizzes.size(); i++) {
        file << (i + 1) << ". " << quizzes[i].toString() << endl;
    }

    file.close();
    cout << "题目文件已保存到: " << filename << endl;
}

void QuizGenerator::saveAnswers(const string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("无法打开文件: " + filename);
    }

    for (size_t i = 0; i < quizzes.size(); i++) {
        file << (i + 1) << ". " << quizzes[i].getResult().toString() << endl;
    }

    file.close();
    cout << "答案文件已保存到: " << filename << endl;
}