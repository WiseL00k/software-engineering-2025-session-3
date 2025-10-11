/**
 * @file QuizGenerator.h
 * @brief ����������Ŀ�������� QuizGenerator����������������Ŀ��𰸡�
 */

#ifndef QUIZ_GENERATOR_H
#define QUIZ_GENERATOR_H

#include <vector>
#include <string>
#include "Expression.h"

 /**
  * @class QuizGenerator
  * @brief �������ɡ��洢��������������Ŀ���𰸡�
  */
class QuizGenerator {
private:
    int numQuestions;             ///< ��Ŀ����
    int range;                    ///< ��ֵ��Χ
    std::vector<Expression> quizzes; ///< ��Ŀ�б�

public:
    /**
     * @brief ���캯��
     * @param n Ҫ���ɵ���Ŀ����
     * @param r ��ֵ��Χ
     */
    QuizGenerator(int n, int r);

    /**
     * @brief ����������Ŀ
     */
    void generateAll();

    /**
     * @brief ����Ŀ���浽�ļ�
     * @param filename �ļ�����Ĭ�� "Exercises.txt"��
     */
    void saveExercises(const std::string& filename = "Exercises.txt") const;

    /**
     * @brief ���𰸱��浽�ļ�
     * @param filename �ļ�����Ĭ�� "Answers.txt"��
     */
    void saveAnswers(const std::string& filename = "Answers.txt") const;
};

#endif // QUIZ_GENERATOR_H
