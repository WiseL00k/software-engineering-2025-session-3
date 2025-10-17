#include "AnswerChecker.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>

/**
 * @brief 校对题目与答案文件
 *
 * 从题目文件（Exercises.txt）与答案文件（Answers.txt）中读取题号与答案，
 * 逐一对比，并将正确与错误题号输出到 Grade.txt 文件中。
 *
 * 文件格式要求：
 * - Exercises.txt: 每行形如 "1. 3 + 5 ="
 * - Answers.txt:   每行形如 "1. 8"
 *
 * 输出文件 Grade.txt 内容示例：
 * ```
 * Correct: 1 3 4 5
 * Wrong: 2
 * Correct: 4 (80%)
 * ```
 *
 * @param exerciseFile 题目文件路径
 * @param answerFile 用户答案文件路径
 * @param outputFile 输出结果文件路径（默认 "Grade.txt"）
 */
void AnswerChecker::checkAnswers(const std::string& exerciseFile,
    const std::string& answerFile,
    const std::string& outputFile)
{
    std::ifstream exFile(exerciseFile);
    std::ifstream ansFile(answerFile);
    std::ofstream outFile(outputFile);

    if (!exFile.is_open() || !ansFile.is_open()) {
        std::cerr << "无法打开题目或答案文件，请检查路径是否正确。" << std::endl;
        return;
    }

    std::vector<std::string> correctAnswers; ///< 标准答案列表
    std::vector<std::string> userAnswers;    ///< 用户答案列表
  
    std::string line;
    // === 读取标准答案文件 ===
    while (std::getline(exFile, line)) {
        // 格式: "1. 3 + 5 = 8"
        auto pos = line.find('=');
        if (pos != std::string::npos) {
            std::string ans = line.substr(pos + 1);
            // 去除空格
            ans.erase(0, ans.find_first_not_of(" \t"));
            ans.erase(ans.find_last_not_of(" \t") + 1);
            correctAnswers.push_back(ans);
        }
    }

    // === 读取用户答案文件 ===
    while (std::getline(ansFile, line)) {
        // 格式: "1. 8"
        auto pos = line.find('.');
        if (pos != std::string::npos) {
            std::string ans = line.substr(pos + 1);
            ans.erase(0, ans.find_first_not_of(" \t"));
            ans.erase(ans.find_last_not_of(" \t") + 1);
            userAnswers.push_back(ans);
        }
    }

    // === 比较答案 ===
    std::vector<int> correctIds;
    std::vector<int> wrongIds;

    int total = std::min(correctAnswers.size(), userAnswers.size());
    for (int i = 0; i < total; ++i) {
        if (correctAnswers[i] == userAnswers[i])
            correctIds.push_back(i + 1);
        else
            wrongIds.push_back(i + 1);
    }

    // === 输出结果 ===
    outFile << "Correct: " << correctIds.size() << "(";
    auto it = correctIds.begin();
    while (it != correctIds.end()) {
        outFile << *it;
        if (++it != correctIds.end()) {
            outFile << ",";
        }
    }
    outFile << ")\n";

    outFile << "Wrong: ";
    for (int id : wrongIds)
        outFile << id << " ";
    outFile << "\n";

    double accuracy = (total == 0) ? 0.0 : (double)correctIds.size() / total * 100.0;
    outFile << "Accuracy: " << accuracy << "%\n";

    std::cout << "批改完成，共 " << total << " 道题，正确 " << correctIds.size()
        << " 道，错误 " << wrongIds.size() << " 道。" << std::endl;
    std::cout << "结果已保存至: " << outputFile << std::endl;
}