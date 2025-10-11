/**
 * @file AnswerChecker.h
 * @brief 定义答案检查器类 AnswerChecker，用于比较标准答案与用户答案。
 */

#ifndef ANSWER_CHECKER_H
#define ANSWER_CHECKER_H

#include <string>
#include <vector>

 /**
  * @class AnswerChecker
  * @brief 对比题目答案文件与用户答案文件，输出正确与错误统计。
  */
class AnswerChecker {
public:
    /**
     * @brief 校对题目与答案文件
     * @param exerciseFile 题目文件路径
     * @param answerFile 用户答案文件路径
     * @param outputFile 输出结果文件路径（默认 "Grade.txt"）
     */
    static void checkAnswers(const std::string& exerciseFile,
        const std::string& answerFile,
        const std::string& outputFile = "Grade.txt");
};

#endif // ANSWER_CHECKER_H
