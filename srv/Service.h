//
// Created by david on 28.03.2022.
//

#ifndef LAB6_7_SERVICE_H
#define LAB6_7_SERVICE_H


#include "../repo/Repo.h"

class Service {
private:
    Repo& repo;
public:
    explicit Service(Repo& rep): repo{rep}{};
    Service(const Service& ot) = delete;
    /*
     * încearcă să adauge. aruncă excepție dacă nu se poate adăuga
     */
    void add(const std::string&, const std::string&, int, const std::string&);
    /*
     * stergere dupa titlu si an
     * arunca exceptie daca nu exista
     */
    void del(const std::string&, int);
    /*
     * modifica un film gasit dupa nume si an
     * se dau noile caracteristici
     */
    void mod(std::string, int, std::string, std::string);
    const std::vector<Movie>& getAll() noexcept;
};


#endif //LAB6_7_SERVICE_H
