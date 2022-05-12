//
// Created by david on 28.03.2022.
//

#include <iostream>
#include "../vector/Vector.h"
#include "Console.h"


void Console::run() {
    while (true) {
        std::cout << "Coș " << srv_.cartSize() << " produse\n";
        std::cout << "Meniu:\n";
        std::cout << "1 adauga || "
                     "2 tipareste\n"
                     "3 Stergere || "
                     "4 modifica\n"
                     "5 cauta || "
                     "6 adauga in cos\n"
                     "7 colire cos\n"
                     "8 exporta cos || 9 importa cos\n"
                     "10 generare cos aleatoriu\n11 undo\n"
                     "0 Iesire\n"
                     "Dati comanda:";
        int cmd;


        try {
            cmd = readInt();
            switch (cmd) {
                case 1:
                    add();
                    break;
                case 2:
                    print(srv_.getAll());
                    break;
                case 3:
                    del();
                    break;
                case 4:
                    modify();
                    break;
                case 5:
                    search();
                    break;
                case 6:
                    addToCart();
                    break;
                case 7:
                    emptyCart();
                    break;
                case 8:
                    exportCart();
                    break;
                case 9:
                    importCart();
                    break;
                case 10:
                    generateCart();
                    break;
                case 11:
                    undo();
                    break;
                case 0:
                    return;
                default:
                    std::cout << "Comanda invalida\n";
            }
        }
        catch (const repoException &ex) {
            std::cout << ex << '\n';
        } catch (const uiException &ex) {
            std::cout << ex << '\n';
        } catch (const fileException &ex) {
            std::cout << ex << '\n';
        }
    }
}

void Console::print(const vector<Movie> &movies) {
    if (movies.empty())
        return;
    std::cout << "Filme\n";
    for (const auto &movie: movies)Console::printOne(movie);
    std::cout << "Sfarsit\n";
}

void Console::printOne(const Movie &movie) {
    std::cout << movie.title() << "||" << movie.genre() << "||" << movie.year() << "||" << movie.protagonist() << "\n";
}

void Console::add() {
    std::string title, genre, protagonist;
    int year;
    std::cout << "titlu:\n";
    std::cin >> title;
    std::cout << "gen:\n";
    std::cin >> genre;
    std::cout << "an:\n";
    year = readInt();
    if (year == -1) {
        std::cout << "trebuie numar!! mai incearca\n";
        return;
    }
    std::cout << "protagonist:\n";
    std::cin >> protagonist;
    srv_.add(title, genre, year, protagonist);
}

void Console::del() {
    std::string title;
    int yea;
    std::cout << "title:";
    std::cin >> title;
    std::cout << "an:";
    yea = readInt();
    if (yea == -1) {
        std::cout << "trebuie numar!! mai incearca\n";
        return;
    }
    srv_.del(title, yea);
}

void Console::modify() {
    std::string title, genre, protagonist;
    int year;
    std::cout << "title:";
    std::cin >> title;
    std::cout << "an:";
    year = readInt();
    if (year == -1) {
        std::cout << "trebuie numar!! mai incearca\n";
        return;
    }
    std::cout << "nou gen:";
    std::cin >> genre;
    std::cout << "nou prot:";
    std::cin >> protagonist;
    srv_.mod(title, year, genre, protagonist);
}

void Console::search() {
    std::string title;
    int year;
    std::cout << "titlu>>";
    std::cin >> title;
    std::cout << "an>>";
    year = readInt();

    printOne(srv_.search(title, year));
}

int Console::readInt() {
    std::string str;
    std::cin >> str;
    int num = 0;
    for (char c: str) {
        if (c < '0' || c > '9')
            throw uiException("trebuie introdus un numar!");
        num = num * 10 + (c - '0');
    }
    return num;
}

void Console::addToCart() {
    std::string title;
    int yea;
    std::cout << "title:";
    std::cin >> title;
    std::cout << "an:";
    yea = readInt();
    if (yea == -1) {
        std::cout << "trebuie numar!! mai incearca\n";
        return;
    }
    srv_.addCart(title, yea);
    std::cout << "coș: " << srv_.cartSize() << " produse\n";
}

void Console::emptyCart() {
    srv_.emptyCart();
    std::cout << "coș " << srv_.cartSize() << " produse\n";
}

void Console::exportCart() {
    std::cout << "Numele fisierului de export (fara spatii): ";
    std::string fileName;
    std::cin >> fileName;
    srv_.exportCart(fileName);
    std::cout << "s-a exportat cu succes in fisierul " << fileName << "\n";
}

void Console::importCart() {
    std::cout << "Numele fisierului de import (fara spatii): ";
    std::string fileName;
    std::cin >> fileName;
    srv_.importCart(fileName);
    std::cout << "s-a importat cu succes din fisierul " << fileName << "\n";
}

void Console::generateCart() {
    int num;
    num = readInt();
    srv_.generateRandomCart(num);
    std::cout<<"s-a generat coșul cu "<<num<<" filme. :)";
}

void Console::undo() {
    srv_.undo();
}


std::ostream &operator<<(std::ostream &out, const uiException &ex) {
    out << ex.msg;
    return out;
}




