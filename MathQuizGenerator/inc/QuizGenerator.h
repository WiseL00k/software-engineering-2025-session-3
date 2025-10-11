/**
 * @file QuizGenerator.h
 * @brief 定义算术题目生成器类 QuizGenerator，用于批量生成题目与答案。
 */

#ifndef QUIZ_GENERATOR_H
#define QUIZ_GENERATOR_H

#include <vector>
#include <string>
#include "Expression.h"

 /**
  * @class QuizGenerator
  * @brief 负责生成、存储与输出多道算术题目及答案。
  */
class QuizGenerator {
private:
    int numQuestions;             ///< 题目数量
    int range;                    ///< 数值范围
    std::vector<Expression> quizzes; ///< 题目列表

public:
    /**
     * @brief 构造函数
     * @param n 要生成的题目数量
     * @param r 数值范围
     */
    QuizGenerator(int n, int r);

    /**
     * @brief 生成所有题目
     */
    void generateAll();

    /**
     * @brief 将题目保存到文件
     * @param filename 文件名（默认 "Exercises.txt"）
     */
    void saveExercises(const std::string& filename = "Exercises.txt") const;

    /**
     * @brief 将答案保存到文件
     * @param filename 文件名（默认 "Answers.txt"）
     */
    void saveAnswers(const std::string& filename = "Answers.txt") const;
};

#endif // QUIZ_GENERATOR_H
