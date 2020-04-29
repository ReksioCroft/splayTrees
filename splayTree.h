//
// Created by reksio on 4/29/20.
//

#ifndef SPLAYTREES_SPLAYTREE_H
#define SPLAYTREES_SPLAYTREE_H

#include "nod.h"

class splayTree {
    nod *radacina;
public:
    splayTree();

    ~splayTree();

    void insert(int nr);
};


#endif //SPLAYTREES_SPLAYTREE_H
