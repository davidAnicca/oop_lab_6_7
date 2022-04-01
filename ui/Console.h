//
// Created by david on 28.03.2022.
//

#ifndef LAB6_7_CONSOLE_H
#define LAB6_7_CONSOLE_H


#include "../srv/Service.h"

class Console {
private:
    Service& srv;
    /*
     * ui adăugare
     */
    void add();
    /*
     * ui afisare
     */
    static void print(const std::vector<Movie>& movies);
    /*
     * ui stergere
     */
    void del();
    /*
     * ui modifcare
     */
    void modify();

public:
    explicit Console(Service& s): srv{s}{};
    void run();
};


#endif //LAB6_7_CONSOLE_H
