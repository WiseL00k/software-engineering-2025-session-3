/**
 * @file Utils.h
 * @brief ����ͨ�ù��ߺ���������������ɡ��ַ�������ȡ�
 */

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace Utils {

    /**
     * @brief ���� [0, max) ��Χ�ڵ��������
     */
    int randInt(int max);

    /**
     * @brief ���ַ������Ϊ�Ӵ�
     * @param s ԭ�ַ���
     * @param delimiter �ָ���
     * @return ��ֽ�����ַ�������
     */
    std::vector<std::string> split(const std::string& s, char delimiter);

}

#endif // UTILS_H
