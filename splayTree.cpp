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
    nodNou->getTata()->setFiu( lastMove, nodCurent );
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
    nod* nodTata = nodCurent->getTata();
    if ( nodCurent->getTata() == radacina ) {
        nodCurent->setTata( nullptr );
        radacina = nodCurent;
    }
    else {
        if ( nodTata->getTata()->getFiu( 1 ) == nodTata )
            nodTata->getTata()->setFiu( 1, nodCurent );
        else
            nodTata->getTata()->setFiu( 2, nodCurent );
        nodCurent->setTata( nodTata->getTata() );
    }

    if ( nodCurent->getFiu( 2 ) != nullptr )
        nodCurent->getFiu( 2 )->setTata( nodTata );
    nodTata->setFiu( 1, nodCurent->getFiu( 2 ) );
    nodTata->setTata( nodCurent );
    nodCurent->setFiu( 2, nodTata );
}

void splayTree::splayLeft( nod* nodCurent ) {
    nod* nodTata = nodCurent->getTata();
    if ( nodCurent->getTata() == radacina ) {
        nodCurent->setTata( nullptr );
        radacina = nodCurent;
    }
    else {
        if ( nodTata->getTata()->getFiu( 1 ) == nodTata )
            nodTata->getTata()->setFiu( 1, nodCurent );
        else
            nodTata->getTata()->setFiu( 2, nodCurent );
        nodCurent->setTata( nodTata->getTata() );
    }

    if ( nodCurent->getFiu( 1 ) != nullptr )
        nodCurent->getFiu( 1 )->setTata( nodTata );
    nodTata->setFiu( 2, nodCurent->getFiu( 1 ) );
    nodTata->setTata( nodCurent );
    nodCurent->setFiu( 1, nodTata );
}