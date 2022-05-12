#include <iostream>
#include "tests/Tests.h"
#include "repo/Repo.h"
#include "srv/Service.h"
#include "tests/VectorTests.h"
#include "ui/Console.h"
#include "repo/cart/cartTest.cpp"
#include "srv/CartTestsSrv.cpp"
#include "undo/UndoTests.cpp"
#include <QApplication>
#include <QLabel>

int main(int argc, char** argv) {


    Tests::runAll();
    ///VectorTests::runAll();
    cartTest::runALl();
    cartTestSrv::runALl();
    runAll();
    Repo r;
    Cart c;
    Service srv{r, c};
    /*
     * Hardcodez niste filme
     */
    srv.add("EnterTheVoid", "Psy", 1990, "Oscar");
    srv.add("LaDoubleVieDeVeroniqe", "Oniric", 1969, "Veronika");
    srv.add("ZazieDansLeMetro", "Adventure", 1960, "PetiteZazie");
    srv.add("LaBelleVerte", "Politc", 1970, "Marie");
    srv.add("PortocalaMecanica", "Oniric", 1960, "Marcel");
    Console cns{srv};
    cns.run();
    return 0;
}
