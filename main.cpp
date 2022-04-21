#include <iostream>
#include "tests/Tests.h"
#include "repo/Repo.h"
#include "srv/Service.h"
#include "tests/VectorTests.h"
#include "ui/Console.h"
#include "repo/cart/cartTest.cpp"
#include "srv/CartTestsSrv.cpp"

int main() {
    Tests::runAll();
    ///VectorTests::runAll();
    cartTest::runALl();
    cartTestSrv::runALl();
    Repo r;
    Cart c;
    Service srv{r, c};
    Console cns{srv};
    cns.run();
    return 0;
}
