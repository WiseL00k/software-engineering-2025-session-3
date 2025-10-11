/**
 * @file AnswerChecker.h
 * @brief ����𰸼������ AnswerChecker�����ڱȽϱ�׼�����û��𰸡�
 */

#ifndef ANSWER_CHECKER_H
#define ANSWER_CHECKER_H

#include <string>
#include <vector>

 /**
  * @class AnswerChecker
  * @brief �Ա���Ŀ���ļ����û����ļ��������ȷ�����ͳ�ơ�
  */
class AnswerChecker {
public:
    /**
     * @brief У����Ŀ����ļ�
     * @param exerciseFile ��Ŀ�ļ�·��
     * @param answerFile �û����ļ�·��
     * @param outputFile �������ļ�·����Ĭ�� "Grade.txt"��
     */
    static void checkAnswers(const std::string& exerciseFile,
        const std::string& answerFile,
        const std::string& outputFile = "Grade.txt");
};

#endif // ANSWER_CHECKER_H
