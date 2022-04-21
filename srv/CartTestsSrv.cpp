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
};

void cartTestSrv::runALl() {
    addGetDelTest();
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
