//
// Created by david on 27.03.2022.
//

#include "Movie.h"

#include <utility>

std::string Movie::title() const {
    return title_;
}

std::string Movie::protagonist() const {
    return protagonist_;
}

int Movie::year() const {
    return year_;
}

std::string Movie::genre() const {
    return genre_;
}

void Movie::set_protagonist(const std::string& newProtagonist){
    protagonist_ = newProtagonist;
}

void Movie::set_year(const int newYear) {
    year_ = newYear;
}

void Movie::set_genre(const std::string& newGenre) {
    genre_ = newGenre;
}

Movie::Movie(const Movie &movie) = default;

Movie::Movie(std::string  title_, std::string  genre, const int year_, std::string  protagonist_):
        title_{std::move(title_)}, genre_{std::move(genre)}, year_{year_}, protagonist_{std::move(protagonist_)}{
}

Movie::~Movie() =default;