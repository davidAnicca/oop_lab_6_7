//
// Created by david on 21.04.2022.
//

//
// Created by david on 21.04.2022.
//
#include <cassert>
#include "../repo/cart/Cart.h"
#include <sstream>

class cartTestSrv{
public:
    static void runALl();

private:
    static void addGetDelTest();

    static void generatorTest();
};

void cartTestSrv::runALl() {
    addGetDelTest();
    generatorTest();
}

void cartTestSrv::addGetDelTest() {
    Repo repo; Cart c;
    Service srv{repo, c};
    for(int i = 0; i < 100; i++){
        std::stringstream ss;
        ss << i;
        std::string title = ss.str();
        srv.add(title, "f00", i%6, "f0o");
    }
    assert(srv.cartSize() == 0);
    for(const auto& movie : repo.getAll()){
        srv.addCart(movie.title(), movie.year());
    }
    assert(srv.cartSize() == 100);
    try{
        srv.addCart("foo", -1);
        assert(false);
    }catch(repoException&){
        assert(true);
    }
    srv.emptyCart();
    assert(srv.cartSize()==0);
}

void cartTestSrv::generatorTest() {
    Repo repo; Cart c;
    Service srv{repo, c};
    srv.add("EnterTheVoid", "Psy", 1990, "Oscar");
    srv.add("LaDoubleVieDeVeroniqe", "Oniric", 1969, "Veronika");
    srv.add("ZazieDansLeMetro", "Adventure", 1960, "PetiteZazie");
    srv.add("LaBelleVerte", "Politc", 1970, "Marie");
    srv.add("PortocalaMecanica", "Oniric", 1960, "Marcel");
    srv.generateRandomCart(966);
    assert(c.getAll().size() == 966);
}
