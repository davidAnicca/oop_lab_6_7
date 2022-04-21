//
// Created by david on 21.04.2022.
//
#include <cassert>
#include "Cart.h"
class cartTest{
public:
    static void runALl();

private:
    static void addGetDelTest();
};

void cartTest::runALl() {
    addGetDelTest();
}

void cartTest::addGetDelTest() {
    Cart cart;
    cart.add(Movie{"a", "b", 1990, "c"});
    assert(cart.getAll().size() == 1);
    cart.add(Movie{"a", "b", 1990, "c"});
    assert(cart.getAll().size() == 2);
    cart.del();
    assert(cart.getAll().empty());
}
