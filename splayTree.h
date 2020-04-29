#ifndef SPLAYTREES_SPLAYTREE_H
#define SPLAYTREES_SPLAYTREE_H


#include "nod.h"


class splayTree {
    nod* radacina;

    void bstInsert( nod* nodNou );

    void splay( nod* nodCurent );

    void splayLeft( nod* nodCurent );

    void splayRight( nod* nodCurent );

    nod* findNodeByValue( int val, nod*& nodTata );

public:
    splayTree();

    // ~splayTree();

    void insert( int nr );

    void deletion( int nr );

    bool find( int nr );

    int lowerBound( int nr );
};


#endif //SPLAYTREES_SPLAYTREE_H
