//
// Created by david on 12.05.2022.
//

#include <sstream>
#include "MyUtils.h"
#include "Console.h"

int MyUtils::stringToInt(const std::string &str) {
    int num = 0;
    for (char c: str) {
        if (c < '0' || c > '9')
            throw uiException("trebuie introdus un numar!");
        num = num * 10 + (c - '0');
    }
    return num;
}

std::vector<std::string> MyUtils::split(const std::string &str) {
    std::vector<std::string> splited;
    std::stringstream ss;
    ss.str("");
    for(const char c: str){
        if(c != ',' && c != '\0'){
            ss<<c;
        }else{
            splited.push_back(ss.str());
            ss.str("");
        }
    }
    splited.push_back(ss.str());
    return splited;
}

std::ostream &operator<<(std::ostream &out, const uiException &ex) {
    out << ex.msg;
    return out;
}
