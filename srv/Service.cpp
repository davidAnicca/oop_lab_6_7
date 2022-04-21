//
// Created by david on 28.03.2022.
//

#include "Service.h"
#include "../repo/Repo.h"
#include "algorithm"
#include <utility>
void Service::add(const std::string& title, const std::string& genre, const int year, const std::string& protagonist) {

    Movie m{title, genre, year, protagonist};
    repo_.add(m);
}

const vector<Movie>& Service::getAll() noexcept{
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

vector<Movie> Service::filter(const std::function<bool(const Movie &)>& condition) const {
    vector<Movie> filtered;
    vector<Movie> all{repo_.getAll()};
    copy_if(all.begin(), all.end(), filtered.begin(), condition);
    return filtered;
}

vector<Movie> Service::filterByYear(int year) const{
    return filter([=](const Movie& movie){
       return movie.year() == year;
    });
}

vector<Movie> Service::filterByTitle(const std::string& title) const{
    return filter([=](const Movie& movie){
        return movie.title() == title;
    });
}



