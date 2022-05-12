//
// Created by david on 12.05.2022.
//

#ifndef HABITAT_UNDO_H
#define HABITAT_UNDO_H
#include <string>
#include <stack>
#include <utility>
#include "Repo.h"

class Undo {
protected:
    ///acest stack memoreaza un movie cu o stare anume
    std::string info;
    Repo &repo_;
public:
    explicit Undo(Repo &repo, const Movie& movie);
    virtual void doUndo(){};
};


#endif //HABITAT_UNDO_H
