#include "App.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

void App::parseArgs(int argc, char** argv) {
    if (argc < 2) {
        cout << "用法: " << endl;
        cout << "生成题目: Myapp.exe -n <题目数量> -r <数值范围>" << endl;
        cout << "批改答案: Myapp.exe -e <题目文件> -a <答案文件>" << endl;
        valid = false;
        return;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            n = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-r") == 0 && i + 1 < argc) {
            r = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            exerciseFile = argv[++i];
        }
        else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
            answerFile = argv[++i];
        }
    }

    // 验证参数
    if (!exerciseFile.empty() && !answerFile.empty()) {
        valid = true;
    }
    else if (n > 0 && r > 0) {
        valid = true;
    }
    else {
        cout << "参数错误！" << endl;
        valid = false;
    }
}

void App::run() {
    if (!valid) return;

    if (!exerciseFile.empty() && !answerFile.empty()) {
        // 批改模式
        AnswerChecker::checkAnswers(exerciseFile, answerFile);
        cout << "批改完成，结果已保存到 Grade.txt" << endl;
    }
    else {
        // 生成模式 + 交互答题
        QuizGenerator generator(n, r);
        generator.generateAll();
        generator.saveExercises();
        generator.saveAnswers();

        cout << "题目生成完成！开始交互答题..." << endl;
        cout << "\n========== 开始答题 ==========" << endl;
        cout << "请输入答案（格式示例：5、1/2、1'1/2）" << endl;
        cout << "=================================" << endl;

        vector<string> userAnswers;
        ifstream exFile("Exercises.txt");
        string line;

        int questionNum = 1;
        while (getline(exFile, line) && questionNum <= n) {
            // 显示题目（去掉换行符）
            if (line.back() == '\n') line.pop_back();
            cout << line << " ";

            string userAnswer;
            cout << "你的答案: ";
            getline(cin, userAnswer);

            // 去除首尾空格
            userAnswer.erase(0, userAnswer.find_first_not_of(" "));
            userAnswer.erase(userAnswer.find_last_not_of(" ") + 1);

            userAnswers.push_back(userAnswer);
            questionNum++;
        }

        exFile.close();

        // 保存用户答案
        ofstream userAnsFile("MyAnswers.txt");
        for (size_t i = 0; i < userAnswers.size(); i++) {
            userAnsFile << (i + 1) << ". " << userAnswers[i] << endl;
        }
        userAnsFile.close();

        cout << "\n=================================" << endl;
        cout << "答题完成！" << endl;
        cout << "你的答案已保存到: MyAnswers.txt" << endl;
        cout << "标准答案已保存到: Answers.txt" << endl;
        cout << "使用以下命令批改: Myapp.exe -e Exercises.txt -a MyAnswers.txt" << endl;
        cout << "=================================" << endl;
    }
}