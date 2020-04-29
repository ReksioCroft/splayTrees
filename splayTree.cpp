#include "splayTree.h"


splayTree::splayTree() {
    radacina = nullptr;
}


splayTree::~splayTree() {
    while ( radacina != nullptr )
        deletion( radacina->getVal() );
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
    nodNou->getTata()->setFiu( lastMove, nodNou );
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


nod* splayTree::findNodeByValue( int val, nod*& nodTata, nod*& lowerBound, nod*& upperBound ) {
    nod* nodCurent = nodTata = radacina;
    lowerBound = upperBound = nullptr;
    while ( nodCurent != nullptr ) {
        if ( nodCurent->getVal() != val )
            nodTata = nodCurent;
        if ( ( lowerBound == nullptr || lowerBound->getVal() < nodCurent->getVal() ) && nodCurent->getVal() <= val )
            lowerBound = nodCurent;
        if ( ( upperBound == nullptr || upperBound->getVal() > nodCurent->getVal() ) && nodCurent->getVal() >= val )
            upperBound = nodCurent;
        if ( nodCurent->getVal() == val )
            return nodCurent;
        else if ( val < nodCurent->getVal() )
            nodCurent = nodCurent->getFiu( 1 );
        else
            nodCurent = nodCurent->getFiu( 2 );
    }
    return nodCurent;
}


bool splayTree::find( int nr ) {
    if ( radacina == nullptr )
        return false;
    nod* nodUltim;
    nod* lowerBound;
    nod* upperBound;
    nod* nodCautat = findNodeByValue( nr, nodUltim, lowerBound, upperBound );
    if ( nodCautat == nullptr ) {
        splay( nodUltim );
        return false;
    }
    else {
        splay( nodCautat );
        return true;
    }
}


void splayTree::deletion( int nr ) {
    nod* nodUltim;
    nod* lowerBound;
    nod* upperBound;
    nod* nodCurent = findNodeByValue( nr, nodUltim, lowerBound, upperBound );

    if ( nodCurent != nullptr ) {
        if ( nodCurent->getFiu( 1 ) == nullptr && nodCurent->getFiu( 2 ) == nullptr ) {
            if ( nodCurent == radacina )
                radacina = nodUltim = nullptr;
            else {
                if ( nodUltim->getFiu( 1 ) == nodCurent )
                    nodUltim->setFiu( 1, nullptr );
                else
                    nodUltim->setFiu( 2, nullptr );
            }
            delete nodCurent;
        }
        else if ( nodCurent->getFiu( 1 ) != nullptr && nodCurent->getFiu( 2 ) == nullptr ) {
            if ( nodCurent == radacina ) {
                radacina = nodCurent->getFiu( 1 );
                nodCurent->getFiu( 1 )->setTata( nullptr );
                nodUltim = nullptr;
            }
            else {
                nodCurent->getFiu( 1 )->setTata( nodUltim );
                if ( nodUltim->getFiu( 1 ) == nodCurent )
                    nodUltim->setFiu( 1, nodCurent->getFiu( 1 ) );
                else
                    nodUltim->setFiu( 2, nodCurent->getFiu( 1 ) );
            }
            delete nodCurent;
        }
        else if ( nodCurent->getFiu( 2 ) != nullptr && nodCurent->getFiu( 1 ) == nullptr ) {
            if ( nodCurent == radacina ) {
                radacina = nodCurent->getFiu( 2 );
                nodCurent->getFiu( 2 )->setTata( nullptr );
                nodUltim = nullptr;
            }
            else {
                nodCurent->getFiu( 2 )->setTata( nodUltim );
                if ( nodUltim->getFiu( 1 ) == nodCurent )
                    nodUltim->setFiu( 1, nodCurent->getFiu( 2 ) );
                else
                    nodUltim->setFiu( 2, nodCurent->getFiu( 2 ) );
            }
            delete nodCurent;
        }
        else {
            nod* nodAux = nodCurent->getFiu( 2 );
            while ( nodAux->getFiu( 1 ) != nullptr )
                nodAux = nodAux->getFiu( 1 );
            nodCurent->setVal( nodAux->getVal() );
            if ( nodAux->getFiu( 2 ) == nullptr ) {
                if ( nodAux->getTata()->getFiu( 1 ) == nodAux )
                    nodAux->getTata()->setFiu( 1, nullptr );
                else
                    nodAux->getTata()->setFiu( 2, nullptr );
            }
            else {
                if ( nodAux->getTata()->getFiu( 1 ) == nodAux ) {
                    nodAux->getTata()->setFiu( 1, nodAux->getFiu( 2 ) );
                    nodAux->getFiu( 2 )->setTata( nodAux->getTata() );
                }
                else{
                    nodAux->getTata()->setFiu( 2, nodAux->getFiu( 2 ) );
                    nodAux->getFiu( 2 )->setTata( nodAux->getTata() );
                }
            }
            delete nodAux;
        }
    }
    if ( nodUltim != nullptr )
        splay( nodUltim );
}


int splayTree::lowerBound( int nr ) {
    nod* nodCurent;
    nod* nodUltim;
    nod* lowerBound;
    nod* upperBound;
    nodCurent = findNodeByValue( nr, nodUltim, lowerBound, upperBound );
    return lowerBound->getVal();
}


int splayTree::upperBound( int nr ) {
    nod* nodCurent;
    nod* nodUltim;
    nod* lowerBound;
    nod* upperBound;
    nodCurent = findNodeByValue( nr, nodUltim, lowerBound, upperBound );
    return upperBound->getVal();
}


nod* splayTree::getRadacina() {
    return radacina;
}


void splayTree::interval( std::ostream& output, nod* nodCurent, int lowerBound, int upperBound ) {
    if ( nodCurent->getFiu( 1 ) != nullptr && nodCurent->getVal() >= lowerBound )
        interval( output, nodCurent->getFiu( 1 ), lowerBound, upperBound );
    if ( nodCurent->getVal() >= lowerBound && nodCurent->getVal() <= upperBound )
        output << nodCurent->getVal() << " ";
    if ( nodCurent->getFiu( 2 ) != nullptr && nodCurent->getVal() <= upperBound )
        interval( output, nodCurent->getFiu( 2 ), lowerBound, upperBound );
}


void splayTree::afisInterval( std::ostream& output, int lowerBound, int upperBound ) {
    interval( output, radacina, lowerBound, upperBound );
    output << '\n';
}