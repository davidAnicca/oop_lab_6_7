//
// Created by david on 27.03.2022.
//

#ifndef LAB6_7_REPO_H
#define LAB6_7_REPO_H

#include <utility>
#include <vector>
#include "../entitie/Movie.h"

class Repo {
private:
    std::vector<Movie> all;
    /*
     * spune dacă un film există sau nu în repo
     */
    bool exist(const Movie &m) const;

public:
    Repo() = default;
    Repo(const Repo& ot) = delete;
    /*
     * adaugă un film. aruncă excepție dacă filmul există deja
     */
    void add(const Movie &m);
    /*
     * returnează toate filmele
     */
    const std::vector<Movie>& getAll() const;
    /*
     * cauta după titlu și an. aruncă excepție dacă nu există
     */
    const Movie& find(const std::string&, int) const;
    /*
     * sterge un film dat. aruncă excepție dacă nu a fost găsit
     */
    void del(Movie &m);
    /*
     * modifica un film dat. aruncă exceptie daca nu e
     */
    void modify(Movie &m);
};

class RepoException: std::exception {
    std::string msg;
public:
    explicit RepoException(std::string  m) :msg{std::move( m )} {}
    //functie friend (vreau sa folosesc membru privat msg)
    friend std::ostream& operator<<(std::ostream& out, const RepoException& ex);
};

std::ostream& operator<<(std::ostream& out, const RepoException& ex);

#endif //LAB6_7_REPO_H
