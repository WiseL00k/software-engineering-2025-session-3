/**
 * @file App.h
 * @brief 定义程序主类 App，负责命令行解析、模块调度与整体运行逻辑。
 */

#ifndef APP_H
#define APP_H

#include <string>
#include "QuizGenerator.h"
#include "AnswerChecker.h"

 /**
  * @class App
  * @brief 主程序控制类，解析命令行参数并调用各模块。
  */
class App {
public:
    /**
     * @brief 默认构造函数
     *
     * 初始化成员变量，设置默认值。
     */
    App() : n(0), r(0), valid(false) {}

    /**
        * @brief 解析命令行参数
        *
        * 该函数解析来自命令行的参数（如题目数量、数值范围等），
        * 并验证参数是否合法。
        *
        * @param argc 参数数量
        * @param argv 参数数组
        */
    void parseArgs(int argc, char** argv);

    /**
     * @brief 运行应用程序主逻辑
     *
     * 调用题目生成、答题、判分等模块，控制整个程序执行。
     */
    void run();
private:
    int n;      ///< 要生成的题目数量
    int r;      ///< 操作数的取值范围
    bool valid; ///< 标记参数是否合法
};

#endif // APP_H
