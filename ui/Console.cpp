//
// Created by david on 28.03.2022.
//

#include <iostream>
#include "../vector/Vector.h"
#include "Console.h"



void Console::run() {
    while (true) {
        std::cout << "Meniu:\n";
        std::cout << "1 adauga\n"
                     "2 tipareste\n"
                     "3 Stergere\n"
                     "4 modifica\n"
                     "5 cauta\n"
                     "0 Iesire\n"
                     "Dati comanda:";
        int cmd;
        cmd = readInt();

        try {
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
                case 0:
                    return;
                default:
                    std::cout << "Comanda invalida\n";
            }
        }
        catch (const repoException &ex) {
            std::cout << ex << '\n';
        }
    }
}

void Console::print(const Vector<Movie>& movies) {
    if(movies.size() == 0)
        return;
    std::cout<<"Filme\n";
    iteratorVector<Movie> it{movies};
    while(it.valid()){
        auto& movie = it.element();
        std::cout<<movie.title()<<"||"<<movie.genre()<<"||"<<movie.year()<<"||"<<movie.protagonist()<<"\n";
        it.next();
    }
    std::cout<<"Sfarsit\n";
}

void Console::printOne(const Movie& movie){
    std::cout<<movie.title()<<"||"<<movie.genre()<<"||"<<movie.year()<<"||"<<movie.protagonist()<<"\n";
}

void Console::add() {
    std::string title, genre, protagonist;
    int year;
    std::cout<<"titlu:\n";
    std::cin>>title;
    std::cout<<"gen:\n";
    std::cin>>genre;
    std::cout<<"an:\n";
    year = readInt();
    if(year == -1){std::cout<<"trebuie numar!! mai incearca\n";add();return;}
    std::cout<<"protagonist:\n";
    std::cin>>protagonist;
    srv_.add(title, genre, year, protagonist);
}

void Console::del() {
    std::string title;
    int yea;
    std::cout<<"title:";
    std::cin>>title;
    yea = readInt();
    if(yea == -1){std::cout<<"trebuie numar!! mai incearca\n";del();return;}
    srv_.del(title, yea);
}

void Console::modify() {
    std::string title, genre, protagonist;
    int year;
    std::cout<<"title:";
    std::cin>>title;
    std::cout<<"an:";
    year = readInt();
    if(year == -1){std::cout<<"trebuie numar!! mai incearca\n";modify();return;}
    std::cout<<"nou gen:";
    std::cin>>genre;
    std::cout<<"nou prot:";
    std::cin>>protagonist;
    srv_.mod(title, year, genre, protagonist);
}

void Console::search() {
    std::string title;
    int year;
    std::cout<<"titlu>>";
    std::cin>>title;
    std::cout<<"an>>";
    year = readInt();
    if(year == -1){std::cout<<"trebuie numar!! mai incearca\n";search();return;}
    printOne(srv_.search(title, year));
}

int Console::readInt() {
    std::string str;
    std::cin>>str;
    int num = 0;
    for(char c:str){
        if(c < '0' || c > '9')
            return -1;
        num += c - '0';
    }
    return num;
}



