// Utils.cpp
#include "Utils.h"
#include <random>
#include <sstream>

using namespace std;

namespace Utils {
    random_device rd;
    mt19937 gen(rd());

    int randInt(int max) {
        if (max <= 0) return 0;
        uniform_int_distribution<> dis(0, max - 1);
        return dis(gen);
    }

    vector<string> split(const string& s, char delimiter) {
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);

        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }

        return tokens;
    }
}