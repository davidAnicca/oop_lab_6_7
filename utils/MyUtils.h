//
// Created by david on 12.05.2022.
//

#ifndef HABITAT_MYUTILS_H
#define HABITAT_MYUTILS_H
#include <vector>
#include <string>


class MyUtils {
public:
    static std::vector<std::string> split(const std::string& str);

    static int stringToInt(const std::string& std);
};

class uiException: std::exception {

public:
    std::string msg;
    explicit uiException(std::string  m) : msg{std::move(m )} {}
    //functie friend (vreau sa folosesc membru privat msg)
    friend std::ostream& operator<<(std::ostream& out, const uiException& ex);
};

std::ostream& operator<<(std::ostream& out, const uiException& ex);



#endif //HABITAT_MYUTILS_H
