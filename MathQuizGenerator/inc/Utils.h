/**
 * @file Utils.h
 * @brief 定义通用工具函数，如随机数生成、字符串处理等。
 */

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace Utils {

    /**
     * @brief 生成 [0, max) 范围内的随机整数
     */
    int randInt(int max);

    /**
     * @brief 将字符串拆分为子串
     * @param s 原字符串
     * @param delimiter 分隔符
     * @return 拆分结果的字符串向量
     */
    std::vector<std::string> split(const std::string& s, char delimiter);

}

#endif // UTILS_H
