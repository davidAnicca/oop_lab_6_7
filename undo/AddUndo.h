//
// Created by david on 12.05.2022.
//

#ifndef HABITAT_ADDUNDO_H
#define HABITAT_ADDUNDO_H


#include "Undo.h"

class AddUndo: public Undo {
public:
    AddUndo(Repo& r, const Movie m): Undo{r, m}{};
    void doUndo() override;
};


#endif //HABITAT_ADDUNDO_H
