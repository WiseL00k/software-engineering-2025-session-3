#include "App.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

void App::parseArgs(int argc, char** argv) {
    if (argc < 2) {
        cout << "�÷�: " << endl;
        cout << "������Ŀ: Myapp.exe -n <��Ŀ����> -r <��ֵ��Χ>" << endl;
        cout << "���Ĵ�: Myapp.exe -e <��Ŀ�ļ�> -a <���ļ�>" << endl;
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

    // ��֤����
    if (!exerciseFile.empty() && !answerFile.empty()) {
        valid = true;
    }
    else if (n > 0 && r > 0) {
        valid = true;
    }
    else {
        cout << "��������" << endl;
        valid = false;
    }
}

void App::run() {
    if (!valid) return;

    if (!exerciseFile.empty() && !answerFile.empty()) {
        // ����ģʽ
        AnswerChecker::checkAnswers(exerciseFile, answerFile);
        cout << "������ɣ�����ѱ��浽 Grade.txt" << endl;
    }
    else {
        // ����ģʽ + ��������
        QuizGenerator generator(n, r);
        generator.generateAll();
        generator.saveExercises();
        generator.saveAnswers();

        cout << "��Ŀ������ɣ���ʼ��������..." << endl;
        cout << "\n========== ��ʼ���� ==========" << endl;
        cout << "������𰸣���ʽʾ����5��1/2��1'1/2��" << endl;
        cout << "=================================" << endl;

        vector<string> userAnswers;
        ifstream exFile("Exercises.txt");
        string line;

        int questionNum = 1;
        while (getline(exFile, line) && questionNum <= n) {
            // ��ʾ��Ŀ��ȥ�����з���
            if (line.back() == '\n') line.pop_back();
            cout << line << " ";

            string userAnswer;
            cout << "��Ĵ�: ";
            getline(cin, userAnswer);

            // ȥ����β�ո�
            userAnswer.erase(0, userAnswer.find_first_not_of(" "));
            userAnswer.erase(userAnswer.find_last_not_of(" ") + 1);

            userAnswers.push_back(userAnswer);
            questionNum++;
        }

        exFile.close();

        // �����û���
        ofstream userAnsFile("MyAnswers.txt");
        for (size_t i = 0; i < userAnswers.size(); i++) {
            userAnsFile << (i + 1) << ". " << userAnswers[i] << endl;
        }
        userAnsFile.close();

        cout << "\n=================================" << endl;
        cout << "������ɣ�" << endl;
        cout << "��Ĵ��ѱ��浽: MyAnswers.txt" << endl;
        cout << "��׼���ѱ��浽: Answers.txt" << endl;
        cout << "ʹ��������������: Myapp.exe -e Exercises.txt -a MyAnswers.txt" << endl;
        cout << "=================================" << endl;
    }
}