//
// Created by david on 12.05.2022.
//

#include "AddUndo.h"
#include "../utils/MyUtils.h"

void AddUndo::doUndo() {
    Undo::doUndo();
    std::string last = info;
    vector<std::string> splitedLine = MyUtils::split(last);
    std::string title=splitedLine[0];
    std::string genre=splitedLine[1];
    int year= MyUtils::stringToInt(splitedLine[2]);
    std::string protagonist =splitedLine[3];
    Movie m{title, genre, year, protagonist};
    repo_.del(m);
}
