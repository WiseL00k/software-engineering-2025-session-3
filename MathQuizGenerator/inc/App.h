/**
 * @file App.h
 * @brief ����������� App�����������н�����ģ����������������߼���
 */

#ifndef APP_H
#define APP_H

#include <string>
#include "QuizGenerator.h"
#include "AnswerChecker.h"

 /**
  * @class App
  * @brief ����������࣬���������в��������ø�ģ�顣
  */
class App {
public:
    /**
     * @brief Ĭ�Ϲ��캯��
     *
     * ��ʼ����Ա����������Ĭ��ֵ��
     */
    App() : n(0), r(0), valid(false) {}

    /**
        * @brief ���������в���
        *
        * �ú����������������еĲ���������Ŀ��������ֵ��Χ�ȣ���
        * ����֤�����Ƿ�Ϸ���
        *
        * @param argc ��������
        * @param argv ��������
        */
    void parseArgs(int argc, char** argv);

    /**
     * @brief ����Ӧ�ó������߼�
     *
     * ������Ŀ���ɡ����⡢�зֵ�ģ�飬������������ִ�С�
     */
    void run();
private:
    int n;      ///< Ҫ���ɵ���Ŀ����
    int r;      ///< ��������ȡֵ��Χ
    bool valid; ///< ��ǲ����Ƿ�Ϸ�
};

#endif // APP_H
