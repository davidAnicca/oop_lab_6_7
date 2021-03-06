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
    /*
     * adaugare în coș
     */
    void addToCart();
    /*
     * golire cos
     */
    void emptyCart();
    /*
     * exporta cos
     */
    void exportCart();
    /*
     * importa cos
     */
    void importCart();
    /*
     * genereaza cos
     */
    void generateCart();
    void undo();
public:
    explicit Console(Service& srv): srv_{srv}{};

    static int readInt();
    void run();

/*
 * printează un singur film
 */
static void printOne(const Movie &movie);
};



#endif //HABITAT_CONSOLE_H
