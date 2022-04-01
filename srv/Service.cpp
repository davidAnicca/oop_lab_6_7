//
// Created by david on 28.03.2022.
//

#include "Service.h"

#include <utility>

void Service::add(const std::string& title, const std::string& genre, const int year, const std::string& protagonist) {

    Movie m{title, genre, year, protagonist};
    repo.add(m);
}

const std::vector<Movie>& Service::getAll() noexcept{
    return repo.getAll();
}

void Service::del(const std::string& title, int year) {
    Movie m = repo.find(title, year);
    repo.del(m);
}

void Service::mod(std::string title, int year, std::string genre, std::string protagonist) {
    Movie m{std::move(title), std::move(genre), year, std::move(protagonist)};
    repo.modify(m);
}



