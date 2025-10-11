#include <iostream>
#include "App.h"

int main(int argc, char** argv)
{
    App app;
    app.parseArgs(argc, argv);
    app.run();
    return 0;
}
