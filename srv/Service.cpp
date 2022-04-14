//
// Created by david on 28.03.2022.
//

#include "Service.h"
#include "../repo/Repo.h"

#include <utility>
void Service::add(const std::string& title, const std::string& genre, const int year, const std::string& protagonist) {

    Movie m{title, genre, year, protagonist};
    repo_.add(m);
}

const Vector<Movie>& Service::getAll() noexcept{
    return repo_.getAll();
}

void Service::del(const std::string& title, int year) {
    Movie m = repo_.find(title, year);
    repo_.del(m);
}

void Service::mod(std::string title, int year, std::string genre, std::string protagonist) {
    Movie m{std::move(title), std::move(genre), year, std::move(protagonist)};
    repo_.modify(m);
}

const Movie &Service::search(const std::string& title, int year) const{
    return repo_.find(title, year);
}

Vector<Movie> Service::filter(std::function<bool(const Movie &)> condition) const {
    Vector<Movie> filtered;
    Vector<Movie> all{repo_.getAll()};
    for(const auto& movie:all){
        if(condition(movie))
            filtered.add(movie);
    }
    return filtered;
}

Vector<Movie> Service::filterByYear(int year) const{
    return filter([=](const Movie& movie){
       return movie.year() == year;
    });
}

Vector<Movie> Service::filterByTitle(const std::string& title) const{
    return filter([=](const Movie& movie){
        return movie.title() == title;
    });
}



