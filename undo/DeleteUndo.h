//
// Created by david on 12.05.2022.
//

#ifndef HABITAT_DELETEUNDO_H
#define HABITAT_DELETEUNDO_H


#include "Undo.h"

class DeleteUndo: public Undo{
public:
    void doUndo() override;
    DeleteUndo(Repo& r, const Movie m): Undo{r, m}{};
};


#endif //HABITAT_DELETEUNDO_H
