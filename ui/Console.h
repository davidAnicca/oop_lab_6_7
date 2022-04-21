//
// Created by david on 28.03.2022.
//

#ifndef HABITAT_CONSOLE_H
#define HABITAT_CONSOLE_H


#include "../srv/Service.h"

class Console {
private:
    Service& srv_;
    /*
     * ui adăugare
     */
    void add();
    /*
     * ui afisare
     */
    static void print(const vector<Movie>& movies);
    /*
     * ui stergere
     */
    void del();
    /*
     * ui modifcare
     */
    void modify();
    /*
     * ui căutare
     */
    void search();

public:
    explicit Console(Service& srv): srv_{srv}{};

    static int readInt();
    void run();

/*
 * printează un singur film
 */
static void printOne(const Movie &movie);
};

class uiException: std::exception {
    std::string msg;
public:
    explicit uiException(std::string  m) : msg{std::move(m )} {}
    //functie friend (vreau sa folosesc membru privat msg)
    friend std::ostream& operator<<(std::ostream& out, const uiException& ex);
};

std::ostream& operator<<(std::ostream& out, const uiException& ex);


#endif //HABITAT_CONSOLE_H
