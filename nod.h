//
// Created by reksio on 4/29/20.
//

#ifndef SPLAYTREES_NOD_H
#define SPLAYTREES_NOD_H


class nod {
    nod *tata;
    nod *fiu1;
    nod *fiu2;
    int val;
public:
    explicit nod(int nr = 0);

    nod *get_fiu(int nrFiu);

    void set_fiu(inr nrFiu, nod *nodNou);

    void set_val(int nr);

    nod *get_tata();

    void set_tata(nod *nodNou);

    ~nod();
};


#endif //SPLAYTREES_NOD_H
