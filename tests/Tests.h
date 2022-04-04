//
// Created by david on 27.03.2022.
//

#ifndef LAB6_7_TESTS_H
#define LAB6_7_TESTS_H


class Tests {
public:
    static void runAll() ;
private:
    /*
     * repo_ tests:
     */
    static void addRepoTest();
    static void createDestroyTest() ;
    static void delRepoTest();
    static void modRepoTest();

    /*
     *srv_ tests:
     */
    static void addSrvTest();
    static void delSrvTest();
    static void modSrvTest();
    static void searchSrvTest();
    static void nameFilterTest();
    static void yearFilterTest();

};


#endif //LAB6_7_TESTS_H
