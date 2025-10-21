#include "App.h"
#include <iostream>
#include <string>
#include <cstdlib>   // atoi
#include <fstream>   // 文件验证

void App::run() const
{
    if (!valid) return;

    // 生成题目模式
    if (n > 0 && r > 0) {
        QuizGenerator generator(n, r);
        generator.generateAll();
        generator.saveExercises("Exercises.txt");
        generator.saveAnswers("Answers.txt");
        std::cout << "已生成 " << n << " 道四则运算题及答案文件。" << std::endl;
    }
    // 批改答案模式
    else {
        if (exerciseFile.empty() || answerFile.empty()) {
            std::cerr << "请指定 -e 和 -a 参数。" << std::endl;
            return;
        }

        AnswerChecker::checkAnswers(exerciseFile, answerFile, "Grade.txt");
        std::cout << "批改完成，结果已保存到 Grade.txt。" << std::endl;
    }
}

void App::parseArgs(int argc, char** argv)
{
    // 参数数量不足，打印帮助
    if (argc < 2) {
        printHelp();
        return;
    }


    // 遍历命令行参数
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 < argc) {
                n = std::atoi(argv[++i]);
            }
            else {
                std::cerr << "错误: -n 参数缺少数值\n";
                return;
            }
        }
        else if (strcmp(argv[i], "-r") == 0) {
            if (i + 1 < argc) {
                r = std::atoi(argv[++i]);
            }
            else {
                std::cerr << "错误: -r 参数缺少数值\n";
                return;
            }
        }
        else if (strcmp(argv[i], "-e") == 0) {
            if (i + 1 < argc) {
                exerciseFile = argv[++i];
            }
            else {
                std::cerr << "错误: -e 参数缺少文件名\n";
                return;
            }
        }
        else if (strcmp(argv[i], "-a") == 0) {
            if (i + 1 < argc) {
                answerFile = argv[++i];
            }
            else {
                std::cerr << "错误: -a 参数缺少文件名\n";
                return;
            }
        }
        else {
            std::cerr << "未知参数: " << argv[i] << "\n";
            printHelp();
            return;
        }
    }

    // 模式判断与参数有效性验证
    if (n > 0 && r > 0) {
        valid = true;  // 生成题目模式
    }
    else if (!exerciseFile.empty() && !answerFile.empty()) {
        valid = true;  // 判题模式

        // 简单验证文件存在
        std::ifstream f1(exerciseFile);
        std::ifstream f2(answerFile);
        if (!f1.is_open() || !f2.is_open()) {
            std::cerr << "错误: 指定的文件不存在或无法打开。\n";
            valid = false;
        }
    }
    else {
        std::cerr << "参数错误：必须指定 -r 参数或 -e/-a 文件。\n";
        printHelp();
        valid = false;
    }
}

void App::printHelp() const {
    std::cout << "----------------------------------------------------------\n"
        << "四则运算自动生成程序\n"
        << "使用方法:\n\n"
        << "  生成题目模式:\n"
        << "    Myapp.exe -n <题目数量> -r <数值范围>\n"
        << "    例如: Myapp.exe -n 10 -r 10\n\n"
        << "  判题模式:\n"
        << "    Myapp.exe -e <题目文件> -a <答案文件>\n"
        << "    例如: Myapp.exe -e Exercises.txt -a Answers.txt\n\n"
        << "注意: -r 参数为生成题目模式必选项，必须指定数值范围。\n"
        << "----------------------------------------------------------\n";
}