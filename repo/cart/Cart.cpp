//
// Created by david on 21.04.2022.
//

#include "Cart.h"

void Cart::add(const Movie &movie) {
    all.push_back(movie);
}

const vector<Movie> &Cart::getAll() const {
    return all;
}

void Cart::del() {
    all.clear();
}
