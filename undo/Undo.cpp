//
// Created by david on 12.05.2022.
//

#include "Undo.h"



Undo::Undo(Repo &repo, const Movie &m) :
    repo_{repo}{
    info = m.title()
           + ","
           + m.genre()
           + ","
           + std::to_string(m.year())
           + ","
           + m.protagonist();
}
