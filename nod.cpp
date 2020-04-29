//
// Created by reksio on 4/29/20.
//

#include "nod.h"

nod::nod(int nr) {
    tata = fiu1 = fiu2 = nullptr;
    val = nr;
}

nod::~nod() {
    tata = fiu1 = fiu2 = nullptr;
    val = nr;
}

nod *nod::get_fiu(int nrFiu) {
    if (nrFiu == 1)
        return fiu1;
    else
        return fiu2;
}

nod *nod::get_tata() {
    return tata;
}

void nod::set_fiu(int nrFiu, nod *nodNou) {
    if (nrFiu == 1)
        fiu1 = nodNou;
    else
        fiu2 = nodNou;
}

void nod::set_tata(nod *nodNou) {
    tata = nodNou;
}

void nod::set_val(int nr) {
    val = nr;
}