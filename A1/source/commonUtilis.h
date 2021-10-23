//
// Created by yurunyang on 2021/10/23.
//

#ifndef UTILIS
#define UTILIS

#include <cstring>
#include <string>
#include <vector>
using namespace std;


//this function is used to split string
vector<string> strsplit(const string& str, const string& delim) {
    vector <string> res;
    if ("" == str) return res;
    //先将要切割的字符串从string类型转换为char*类型
    char *strs = new char[str.length() + 1]; //不要忘了
    strcpy(strs, str.c_str());

    char *d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while (p) {
        string s = p; //分割得到的字符串转换为string类型
        res.push_back(s); //存入结果数组
        p = strtok(NULL, d);
    }

    return res;
}

#endif