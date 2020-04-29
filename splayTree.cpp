#include "splayTree.h"

splayTree::splayTree() {
    radacina = nullptr;
}

void splayTree::insert( int nr ) {
    nod* nodNou = new nod( nr );
    if ( radacina == nullptr ) {
        radacina = nodNou;
    }
    else {
        bstInsert( nodNou );
        splay( nodNou );
    }
}

void splayTree::bstInsert( nod* nodNou ) {
    nod* nodCurent = radacina;
    int lastMove = 1;
    while ( nodCurent != nullptr ) {
        nodNou->setTata( nodCurent );
        if ( nodNou->getVal() < nodCurent->getVal() ) {
            nodCurent = nodCurent->getFiu( 1 );
            lastMove = 1;
        }
        else {
            nodCurent = nodCurent->getFiu( 2 );
            lastMove = 2;
        }
    }
    nodCurent->getTata()->setFiu( lastMove, nodCurent );
}

void splayTree::splay( nod* nodCurent ) {
    if ( nodCurent->getTata() == radacina ) {
        if ( nodCurent->getTata()->getFiu( 1 ) == nodCurent ) {
            ///daca sunt fiul din stanga al radacinii => "Zig Rotation"
            splayRight( nodCurent );
        }
        else {
            splayLeft( nodCurent );
            ///daca sunt fiul din dreapta al radacinii => "Zag Rotation"

        }
    }
    else if ( nodCurent != radacina ) { ///daca mai continui
        nod* nodTata = nodCurent->getTata();
        if ( nodCurent->getTata()->getFiu( 1 ) == nodCurent ) {
            ///sunt un fiu stang => Zig-zig sau Zig-zag
            if ( nodTata->getTata()->getFiu( 1 ) == nodTata ) {
                ///Zig-Zig step
                splayRight( nodTata );
                splayRight( nodCurent );
            }
            else {
                ///zig-zag
                splayRight( nodCurent );
                splayLeft( nodCurent );
            }

        }
        else {
            if ( nodTata->getTata()->getFiu( 2 ) == nodTata ) {
                ///zag-zag
                splayLeft( nodTata );
                splayLeft( nodCurent );
            }
            else {
                ///zag-zig
                splayLeft( nodCurent );
                splayRight( nodCurent );

            }
        }
        splay( nodCurent );
    }
}

void splayTree::splayRight( nod* nodCurent ) {
    if ( nodCurent->getTata() == radacina ) {
        if ( nodCurent->getFiu( 2 ) != nullptr )
            nodCurent->getFiu( 2 )->setTata( radacina );
        radacina->setFiu( 1, nodCurent->getFiu( 2 ) );
        radacina->setTata( nodCurent );
        nodCurent->setTata( nullptr );
        nodCurent->setFiu( 2, radacina );
        radacina = nodCurent;
    }
    else {
        ///Todo
    }
}

void splayTree::splayLeft( nod* nodCurent ) {
    if ( nodCurent->getTata() == radacina ) {
        if ( nodCurent->getFiu( 1 ) != nullptr )
            nodCurent->getFiu( 1 )->setTata( radacina );
        radacina->setFiu( 2, nodCurent->getFiu( 1 ) );
        radacina->setTata( nodCurent );
        nodCurent->setTata( nullptr );
        nodCurent->setFiu( 1, radacina );
        radacina = nodCurent;
    }
    else{
        ///Todo
    }
}