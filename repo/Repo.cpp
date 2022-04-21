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
    all.push_back(m);
}

const vector<Movie>& Repo::getAll() const {
    return all;
}

const Movie& Repo::find(const std::string& title, const int year) const{
    for(auto& m : all){
        const Movie& movie = m;
        if(movie.title() == title && movie.year() == year)
            return movie;
    }
    throw repoException("nu exista");
}

void Repo::del(Movie &m) {
    if(!exist(m))
        throw repoException("nu există");
    for(int i = 0; i < all.size(); i++){
        if(all[i] == m){
            all.erase(all.begin() +i);
            return;
        }
    }
}

void Repo::modify(Movie& movie) {
    if(!exist(movie))
        throw repoException("nu exista");
    for(auto & i : all){
        Movie m = i;
        if(m == movie){
            i = movie;
            return;
        }
    }
}


std::ostream &operator<<(std::ostream &out, const repoException &ex) {
    out << ex.msg;
    return out;
}
