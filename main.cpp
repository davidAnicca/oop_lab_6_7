#include <iostream>
#include "tests/Tests.h"
#include "repo/Repo.h"
#include "srv/Service.h"
#include "ui/Console.h"

int main() {
    Tests tests;
    tests.runAll();
    Repo r;
    Service srv{r};
    Console cns{srv};
    cns.run();
    return 0;
}
