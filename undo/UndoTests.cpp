//
// Created by david on 12.05.2022.
//

#include <cassert>
#include "Repo.h"
#include "Service.h"

void undoDeleteTest(){
    Repo r;
    Cart c;
    Service srv{r, c};
    srv.add("EnterTheVoid", "Psy", 1990, "Oscar");
    srv.add("LaDoubleVieDeVeroniqe", "Oniric", 1969, "Veronika");
    srv.add("ZazieDansLeMetro", "Adventure", 1960, "PetiteZazie");
    srv.add("LaBelleVerte", "Politc", 1970, "Marie");
    srv.add("PortocalaMecanica", "Oniric", 1960, "Marcel");
    srv.del("EnterTheVoid", 1990);
    srv.undo();
    assert(srv.getAll().size()==5);
}

void undoAddTest(){
    Repo r;
    Cart c;
    Service srv{r, c};
    srv.add("EnterTheVoid", "Psy", 1990, "Oscar");
    srv.add("LaDoubleVieDeVeroniqe", "Oniric", 1969, "Veronika");
    srv.add("ZazieDansLeMetro", "Adventure", 1960, "PetiteZazie");
    srv.add("LaBelleVerte", "Politc", 1970, "Marie");
    srv.add("PortocalaMecanica", "Oniric", 1960, "Marcel");
    srv.undo();
    assert(srv.getAll().size()==4);
    for(int i = 1; i <= 4; i++)srv.undo();
    assert(srv.getAll().size()==0);
}

void undoModTest(){
    Repo r;
    Cart c;
    Service srv{r, c};
    srv.add("EnterTheVoid", "Psy", 1990, "Oscar");
    srv.mod("EnterTheVoid", 1990, "foo", "f");
    srv.undo();
    assert(srv.getAll()[0].genre()=="Psy" && srv.getAll()[0].protagonist()=="Oscar");
}

void runAll(){
    undoModTest();
    undoDeleteTest();
    undoAddTest();
}
