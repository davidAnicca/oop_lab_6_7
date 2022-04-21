//
// Created by david on 28.03.2022.
//

#ifndef LAB6_7_SERVICE_H
#define LAB6_7_SERVICE_H


#include <functional>
#include "../repo/Repo.h"
#include "../repo/cart/Cart.h"

class Service {
private:
    Repo &repo_;
    Cart &cart_;
public:
    explicit Service(Repo &repo, Cart &cart) : repo_{repo}, cart_{cart} {};

    Service(const Service &other) = delete;

    /*
     * încearcă să adauge. aruncă excepție dacă nu se poate adăuga
     */
    void add(const std::string &title,
             const std::string &genre,
             int year,
             const std::string &protagonist);

    /*
     * stergere dupa titlu si an
     * arunca exceptie daca nu exista
     */
    void del(const std::string &title,
             int year);

    /*
     * modifica un film gasit dupa nume si an
     * se dau noile caracteristici
     */
    void mod(std::string title,
             int year,
             std::string newGenre,
             std::string newProtagonist);

    const vector<Movie> &getAll() noexcept;

    /*
     * caută un film după titlu și an. aruncă excepție dacă nu există
     */
    const Movie &search(const std::string &title, int year) const;

    vector<Movie> filter(const std::function<bool(const Movie &)> &condition) const;

    vector<Movie> filterByYear(int year) const;

    vector<Movie> filterByTitle(const std::string &title) const;

    /*
     * încearcă să adauge. aruncă excepție dacă nu se poate adăuga
     */
    void addCart(const std::string &title, int year);

    void emptyCart();

    int cartSize();

    void exportCart();

};

#endif //LAB6_7_SERVICE_H
