//
// Created by david on 27.03.2022.
//

#include <cassert>
#include <iostream>
#include <sstream>
#include "Tests.h"
#include "../entitie/Movie.h"
#include "../repo/Repo.h"
#include "../srv/Service.h"


void Tests::runAll() {
    createDestroyTest();

    addRepoTest();
    delRepoTest();
    modRepoTest();


    addSrvTest();
    delSrvTest();
    modSrvTest();
    searchSrvTest();
//    yearFilterTest();
//    nameFilterTest();
    std::cout<<"tests ok";
}

void Tests::createDestroyTest() {
    Movie m{"enter the void", "psychedelic", 2009, "Oscar"};
    assert(m.title() == "enter the void");
    assert(m.genre() == "psychedelic");
    assert(m.year() == 2009);
    assert(m.protagonist() == "Oscar");
    Movie m2{"enter the void", "psychedelic", 2009, "Oscar"};
    assert(m == m2);
    m2.set_genre("newgenre");
    m2.set_protagonist("protag");
    m2.set_year(1999);
    assert(m2.protagonist() == "protag");
    assert(m2.year() == 1999);
    assert(m2.genre() == "newgenre");
    m = m2;
    assert(m.protagonist() == "protag");
    assert(m.year() == 1999);
    assert(m.genre() == "newgenre");
}

void Tests::addRepoTest() {
    Repo repo;
    Movie m{"enter the void", "psychedelic", 2009, "Oscar"};
    repo.add(m);
    assert(repo.getAll().size() == 1);
    Movie found = repo.find("enter the void", 2009);
    assert(found == m);
    Movie m2{"La Double Vie De Veronique", "Drama", 1996, "Veronika"};
    repo.add(m2);
    found = repo.find("La Double Vie De Veronique", 1996);
    assert(found == m2);
    assert(repo.getAll().size() == 2);
    ///adaugare multiplă !
    try{
        repo.add(m);
        assert(false);
    }catch(repoException& e){
        assert(true);
    }
    //cauta inexistent
    try {
        repo.find("c", 1990);
        assert(false);
    }
    catch (const repoException& e) {
        std::stringstream os;
        os << e;
        assert(os.str().find("nu exista")>=0);
    }
}

void Tests::addSrvTest() {
    Repo r;
    Service srv{r};
    srv.add("Enter The Void", "Psychedelic", 2009, "Oscar");
    assert(r.getAll().size() == 1);
    try{
        ///adăugare multiplă
        srv.add("Enter The Void", "a", 2009, "a");
        assert(false);
    }catch(repoException&){
        assert(true);
    }
}

void Tests::delRepoTest() {
    Repo repo;
    Movie m{"enter the void", "psychedelic", 2009, "Oscar"};
    repo.add(m);
    Movie m2{"La Double Vie De Veronique", "Drama", 1996, "Veronika"};
    repo.add(m2);
    repo.del(m);
    assert(repo.getAll().size() ==1);
    repo.del(m2);
    assert(repo.getAll().size()==0);
    try{
        repo.del(m);
        assert(false);
    }catch(repoException&){
        assert(true);
    }

}

void Tests::delSrvTest() {
    Repo repo;
    Movie m{"enter the void", "psychedelic", 2009, "Oscar"};
    repo.add(m);
    Movie m2{"La Double Vie De Veronique", "Drama", 1996, "Veronika"};
    repo.add(m2);
    Service srv{repo};
    srv.del("enter the void", 2009);
    assert(srv.getAll().size() == 1);
    srv.del("La Double Vie De Veronique", 1996);
    assert(srv.getAll().size()==0);
    try{
        srv.del("foo", 1);
        assert(false);
    }catch(repoException&){
        assert(true);
    }
}

void Tests::modRepoTest() {
    Repo repo;
    Movie m{"enter the void", "psychedelic", 2009, "Oscar"};
    repo.add(m);
    Movie m2{"La Double Vie De Veronique", "Drama", 1996, "Veronika"};
    repo.add(m2);
    Movie newM{"enter the void", "psy", 2009, "osky"};
    repo.modify(newM);
    assert(repo.find("enter the void", 2009).genre() == "psy"
    && repo.find("enter the void", 2009).protagonist() == "osky");
    try{
        Movie mm{"foo", "foo", 1, "foo"};
        repo.modify(mm);
        assert(false);
    }catch(repoException&){
        assert(true);
    }
}

void Tests::modSrvTest() {
    Repo repo;
    Movie m{"enter the void", "psychedelic", 2009, "Oscar"};
    repo.add(m);
    Movie m2{"La Double Vie De Veronique", "Drama", 1996, "Veronika"};
    repo.add(m2);
    Service srv{repo};
    srv.mod("enter the void", 2009, "psy", "osky");
    assert(repo.find("enter the void", 2009).genre() == "psy"
           && repo.find("enter the void", 2009).protagonist() == "osky");
    try{
        srv.mod("foo", 1, "foo", "foo");
        assert(false);
    }catch(repoException&){
        assert(true);
    }
}

void Tests::searchSrvTest() {
    Repo repo;
    Movie m{"enter the void", "psychedelic", 2009, "Oscar"};
    repo.add(m);
    Movie m2{"La Double Vie De Veronique", "Drama", 1996, "Veronika"};
    repo.add(m2);
    Service srv{repo};
    Movie found = srv.search("enter the void", 2009);
    assert(found == m);
    Movie found2 = srv.search("La Double Vie De Veronique", 1996);
    assert(found2 == m2);
    try{
        srv.search("foo", 0);
        assert(false);
    }catch(repoException&){
        assert(true);
    }
}

void Tests::yearFilterTest() {
    Repo repo;
    Service srv{repo};
    for(int i = 0; i < 100; i++){
        std::stringstream ss;
        ss << i;
        std::string title = ss.str();
        srv.add(title, "f00", i%6, "f0o");
    }
    Vector<Movie> filtered = srv.filterByYear(5);
    assert(filtered.size()!=0);
    for(int i = 0; i < filtered.size(); i++){
        assert(filtered.get(i).year() == 5);
    }
    for(const auto& movie : filtered){
        assert(movie.year() == 5);
    }

}

void Tests::nameFilterTest() {
    Repo repo;
    Service srv{repo};
    for(int i = 0; i < 100; i++){
        std::stringstream ss;
        ss << i%6;
        std::string title = ss.str();
        srv.add(title, "f00", i, "f0o");
    }
    Vector<Movie> filtered = srv.filterByTitle("5");
    assert(filtered.size()!=0);
    for(int i = 0; i < filtered.size(); i++){
        assert(filtered.get(i).title() == "5");
    }
    for(const auto& movie : filtered){
        std::cout<<&movie;
        assert(movie.title() == "5");
    }
}
