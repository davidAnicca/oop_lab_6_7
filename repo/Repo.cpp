//
// Created by david on 27.03.2022.
//

#include "Repo.h"

bool Repo::exist(const Movie &m) const {
    try{
        find(m.title(), m.year());
        return true;
    }catch(repoException&){
        return false;
    }
}

void Repo::add(const Movie &m) {
    if(exist(m))
        throw repoException("deja exista");
    all.add(m);
}

const Vector<Movie>& Repo::getAll() const {
    return all;
}

const Movie& Repo::find(const std::string& title, const int year) const{
    for(int i = 0; i < all.size(); i++){
        Movie& movie = all.get(i);
        if(movie.title() == title && movie.year() == year)
            return movie;
    }
    throw repoException("nu exista");
}

void Repo::del(Movie &m) {
    if(!exist(m))
        throw repoException("nu există");
    for(int i = 0; i < all.size(); i++){
        if(all.get(i) == m){
            all.erase(i);
            return;
        }
    }
}

void Repo::modify(Movie& movie) {
    if(!exist(movie))
        throw repoException("nu exista");
    for(int i = 0; i < all.size(); i++){
        Movie m = all.get(i);
        if(m == movie){
            all.set(i, movie);
            return;
        }
    }
}


std::ostream &operator<<(std::ostream &out, const repoException &ex) {
    out << ex.msg;
    return out;
}
