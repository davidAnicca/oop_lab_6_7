//
// Created by david on 28.03.2022.
//

#ifndef LAB6_7_SERVICE_H
#define LAB6_7_SERVICE_H


#include <functional>
#include "../repo/Repo.h"

class Service {
private:
    Repo& repo_;
public:
    explicit Service(Repo& repo): repo_{repo}{};
    Service(const Service& other) = delete;
    /*
     * încearcă să adauge. aruncă excepție dacă nu se poate adăuga
     */
    void add(const std::string& title,
             const std::string& genre,
             int year,
             const std::string& protagonist);
    /*
     * stergere dupa titlu si an
     * arunca exceptie daca nu exista
     */
    void del(const std::string& title,
             int year);
    /*
     * modifica un film gasit dupa nume si an
     * se dau noile caracteristici
     */
    void mod(std::string title,
             int year,
             std::string newGenre,
             std::string newProtagonist);

    const Vector<Movie>& getAll() noexcept;
    /*
     * caută un film după titlu și an. aruncă excepție dacă nu există
     */
    const Movie& search(const std::string& title, int year) const;

    Vector<Movie> filter(std::function<bool(const Movie &)> condition) const;

    Vector<Movie> filterByYear(int year) const;

    Vector<Movie> filterByTitle(const std::string& title) const;
};


#endif //LAB6_7_SERVICE_H
