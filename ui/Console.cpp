//
// Created by david on 28.03.2022.
//

#include <iostream>
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
        std::cin >> cmd;
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
        catch (const RepoException &ex) {
            std::cout << ex << '\n';
        }
    }
}

void Console::print(const std::vector<Movie>& movies) {
    if(movies.empty())
        return;
    std::cout<<"Filme\n";
    for(auto& movie:movies){
        std::cout<<movie.title()<<"||"<<movie.genre()<<"||"<<movie.year()<<"||"<<movie.protagonist()<<"\n";
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
    std::cin>>year;
    std::cout<<"protagonist:\n";
    std::cin>>protagonist;
    srv_.add(title, genre, year, protagonist);
}

void Console::del() {
    std::string title;
    int yea;
    std::cout<<"title:";
    std::cin>>title;
    std::cout<<"an:";
    std::cin>>yea;
    srv_.del(title, yea);
}

void Console::modify() {
    std::string title, genre, protagonist;
    int year;
    std::cout<<"title:";
    std::cin>>title;
    std::cout<<"an:";
    std::cin>>year;
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
    std::cin>>year;
    printOne(srv_.search(title, year));
}



