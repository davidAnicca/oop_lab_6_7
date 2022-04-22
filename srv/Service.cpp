//
// Created by david on 28.03.2022.
//

#include "Service.h"
#include "../repo/Repo.h"
#include "Console.h"
#include <utility>
#include <fstream>
#include <algorithm>
#include <random> // std::default_random_engine
#include <chrono>
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

void Service::addCart(const std::string &title, int year) {
    Movie m = repo_.find(title, year);
    cart_.add(m);
}

void Service::emptyCart() {
    cart_.del();
}

int Service::cartSize() {
    return cart_.getAll().size();
}

void Service::importCart(const std::string& fileName) {
    std::ifstream fileStream(fileName);
    if(!fileStream.is_open()){
        throw fileException("A aparut o eroare la import\n"
                            "Cel mai probabil fisierul nu a putut fi deschis sau acesta nu exista:(");
    }
    std::string title, genre, protagonist;
    int year;
    int nr=0;
    while(fileStream>>title
    && fileStream>>genre
    && fileStream>>year
    && fileStream>>protagonist){
        try{
            addCart(title, year);
        }catch(repoException &R){
            nr++;
        }
    }
    fileStream.close();
    if(nr > 0){
        throw fileException("cateva filme nu au putut fi adaugate\n"
                            "cel mai probabil ele nu mai exista în magazin");
    }
}

void Service::exportCart(const std:: string& fileName) {
    std:: ofstream fileStream(fileName);
    for(const auto& movie : cart_.getAll()){
        fileStream<<movie.title()<<" "<<movie.genre()<<" "<<movie.year()<<" "<<movie.protagonist()<<"\n";
    }
    fileStream.close();
}

void Service::generateRandomCart(int num) {
    if(repo_.getAll().empty())
        return;
    vector<Movie> v = repo_.getAll();
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, v.size()-1);
    int rndNr = dist(mt);
    int i=0;
    while(i < num){
        i++;
        addCart(v[rndNr].title(), v[rndNr].year());
        rndNr = dist(mt);
    }
}


std::ostream &operator<<(std::ostream &out, const fileException &ex) {
    out<<ex.msg;
    return out;
}
