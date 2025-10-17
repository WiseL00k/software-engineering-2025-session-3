#include <iostream>
#include "App.h"

int main(int argc, char** argv)
{
    try {
        App app;
        app.parseArgs(argc, argv);
        app.run();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "程序运行出错: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "未知错误发生" << std::endl;
        return 1;
    }
}
