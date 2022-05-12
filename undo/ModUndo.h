//
// Created by david on 12.05.2022.
//

#ifndef HABITAT_MODUNDO_H
#define HABITAT_MODUNDO_H


#include "Undo.h"

class ModUndo: public Undo{
public:
    void doUndo() override;
    ModUndo(Repo& r, const Movie& m):Undo{r, m}{};
};


#endif //HABITAT_MODUNDO_H
