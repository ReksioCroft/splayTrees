#ifndef SPLAYTREES_SPLAYTREE_H
#define SPLAYTREES_SPLAYTREE_H


#include "nod.h"
#include "fstream"


class splayTree {
    nod* radacina;

    void bstInsert( nod* nodNou );

    void splay( nod* nodCurent );

    void splayLeft( nod* nodCurent );

    void splayRight( nod* nodCurent );

    nod* findNodeByValue( int val, nod*& nodTata, nod*& lowerBound, nod*& upperBound );

    void interval( std::ostream& output, nod* nodCurent, int lowerBound, int uperBound );

public:
    splayTree();

    // ~splayTree();

    void insert( int nr );

    void deletion( int nr );

    bool find( int nr );

    int lowerBound( int nr );

    int upperBound( int nr );

    void afisInterval( std::ostream& output, int lowerBound, int uperBound );

    nod* getRadacina();
};


#endif //SPLAYTREES_SPLAYTREE_H
