//
// Created by david on 27.03.2022.
//

#ifndef LAB6_7_MOVIE_H
#define LAB6_7_MOVIE_H

#include <string>
#include <iostream>

class Movie {
private:
    std::string title_;
    std::string genre_;
    int year_;
    std::string protagonist_;
public:
    /*/
     * operatorul de atribuire (copiere)
     */
    Movie& operator=(const Movie& movie){
        if(this == &movie) {
            return *this;
        }
        title_ = movie.title_;
        genre_ = movie.genre_;
        year_ = movie.year_;
        protagonist_ = movie.protagonist_;
        return *this;
    }
    /*
     * operatorul de egalitate
     */
    bool operator==(const Movie& movie){
        if(this == &movie)
            return true;
        return title_ == movie.title_ && year_ == movie.year_;
    }
    /*
     * returneaza titlul
     */
    std::string title() const;
    /*
     * returneaza genul
     */
    std::string genre() const;
    /*
     * returnează anul apariției
     */
    int year() const;
    /*
     * returnează protagonistul
     */
    std::string protagonist() const;

    /*
     * setter pt gen
     */
    void set_genre(const std::string& genre);
    /*
    * setter pt an
    */
    void set_year(int year);
    /*
    * setter pt protagonist
    */
    void set_protagonist(const std::string& protagonist);
    Movie()=default;
    /*
     * contructor pt film bazat pe parametri
     */
    Movie(std::string title, std::string genre, int year, std::string protagonist);
    /*
     * constructor copie
     */
    Movie(const Movie& movie);
    /*
     * destructor
     */
    ~Movie();
};


#endif //LAB6_7_MOVIE_H
