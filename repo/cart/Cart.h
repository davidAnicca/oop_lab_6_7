//
// Created by david on 21.04.2022.
//

#ifndef HABITAT_CART_H
#define HABITAT_CART_H


#include "Movie.h"
#include "vector"
using std::vector;

class Cart {
private:
    vector<Movie> all;

public:
    Cart() = default;
    Cart(const Cart& other) = delete;

    void add(const Movie &movie);
    const vector<Movie>& getAll() const;
    void del();
};


#endif //HABITAT_CART_H
