//
// Created by david on 15.04.2022.
//

#include <vector>
#include "../vector/Vector.h"
#include "VectorTests.h"
#include "Movie.h"
#include <assert.h>

template <typename MyVector>
MyVector testCopyIterate(MyVector v) {
    double totalPrice = 0;
    for (auto el : v) {
        totalPrice += el.year();
    }
    Movie p{"foo", "foo", 1, "foo"};
    v.add(p);
    return v;
}

template <typename MyVector>
void addPets(MyVector& v, int cate) {
    for (int i = 0; i<cate; i++) {
        Movie p{"foo", "foo", 1, "foo"};
        v.add(p);
    }
}

/*
Testare constructori / assignment
E template pentru a refolosi la diferite variante de VectorDinamic din proiect
*/
template <typename MyVector>
void testCreateCopyAssign() {
    MyVector v;//default constructor
    addPets(v, 100);
    assert(v.size() == 100);
    assert(v.get(50).title() == "foo");

    MyVector v2{ v };//constructor de copiere
    assert(v2.size() == 100);
    assert(v2.get(50).title() == "foo");

    MyVector v3;//default constructor
    v3 = v;//operator=   assignment
    assert(v3.size() == 100);
    assert(v3.get(50).title() =="foo");

    auto v4 = testCopyIterate(v3);
    assert(v4.size() == 101);
    assert(v4.get(50).title() =="foo");
}

/*
  Test pentru move constructor si move assgnment
*/
template <typename MyVector>
void testMoveConstrAssgnment() {
    std::vector<MyVector> v;
    //adaugam un vector care este o variabila temporara
    //se v-a apela move constructor
    v.push_back(MyVector{});

    //inseram, la fel se apeleaza move costructor de la vectorul nostru
    v.insert(v.begin(),MyVector{});

    assert(v.size() == 2);

    MyVector v2;
    addPets(v2, 50);

    v2 = MyVector{};//move assignment

    assert(v2.size() == 0);

}
template <typename MyVector>
void testAll() {
    testCreateCopyAssign<MyVector>();
    testMoveConstrAssgnment<MyVector>();
}

void VectorTests::runAll() {
    testAll<Vector<Movie>>();
}
