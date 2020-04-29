#include <fstream>
#include "splayTree.h"


int main() {
    std::ifstream fin( "abce.in" );
    std::ofstream fout( "abce.out" );
    int nr, test, x, y, i;
    splayTree tree;
    fin >> nr;
    for ( i = 0; i < nr; i++ ) {
        fin >> test >> x;
        switch ( test ) {
            case 1:
                tree.insert( x );
                break;
            case 2:
                tree.deletion( x );
                break;
            case 3:
                fout << tree.find( x ) << "\n";
                break;
            case 4:
                fout << tree.lowerBound( x ) << "\n";
                break;
            case 5:
                fout << tree.upperBound( x ) << "\n";
                break;
            case 6:
                fin >> y;
                tree.afisInterval( fout, x, y );
        }
    }
    fin.close();
    fout.close();
    return 0;
}
