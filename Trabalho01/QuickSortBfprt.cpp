//
// Created by fbeze on 02/04/2019.
//

#include "QuickSortBfprt.h"

QuickSortBfprt::QuickSortBfprt() = default;

tuple<int *, int *> QuickSortBfprt::LomutoTriplePartitioning_(int *init, int *fin, int *&pivot) {
    Swap_(init, pivot);
    int *i = init;
    int *j = init+1;
    int *m = init;

    for (; j <= fin; ++j) {
        if(*j < *init){
            i++;
            Swap_(i,j);

            m++;
            Swap_(m,i);

        }

        else if(*j == *init){
            i++;
            Swap_(i,j);
        }
    }
    Swap_(m, init);
    pivot = i;
    return make_tuple(m, i);
}

void QuickSortBfprt::QuickSort_(int *init, int *fin) {
    int *initR;
    int *finL;
    int *r, *s;
    int *i;


    if (fin <= init){
        return;
    }
    BFPRT(init, i, fin);
    

    if(i > init ){
        finL = i - 1;
        QuickSort_(init, finL);
    }

    if(i < fin ){
        initR = i + 1;
        QuickSort_(initR, fin);

    }
}

void QuickSortBfprt::HoareSelection(int *init, int *fin, int *iPivot) {
    int *pivot = ChoosePivot_(init, fin);

    Swap_(init, pivot);

    int *i = init;
    int *j = i + 1;

    for (j; j <= fin; ++j) {
        if(*j < *init){
            i = i + 1;
            Swap_(i,j);
        }
    }
    Swap_(i, init);
    pivot = i;

    if (iPivot == pivot){
        return;
    }

    if (iPivot < pivot){
        HoareSelection(init, pivot-1, iPivot);
    }

    else{
        HoareSelection(pivot + 1, fin, iPivot);
    }

}

void QuickSortBfprt::BFPRT(int *init, int *&i, int *fin) {
    int *middle = init + (fin - init)/2;
    int *auxI = init;
    int *auxF = init + 4;
    int *u = init; //Variable to swap the medians with the firsts places

    if ((fin - init) <= 5){
        HoareSelection(init, fin, middle);
        i = middle;
        return;
    }

    while(auxI <= fin){
        middle = ChoosePivot_(auxI, auxF);
        HoareSelection(auxI, auxF, middle);
        Swap_(u, middle);
        auxI = auxF + 1;
        if(fin - auxF < 5){
            auxF = auxF + (fin - auxF);
        }
        else{
            auxF = auxF + 4;
        }
        u = u + 1;

    }

    BFPRT(init, i, u);
    tuple <int*, int*> pivos = LomutoTriplePartitioning_(init, fin, i);

    if (i >= get<0>(pivos) || get<1>(pivos) >= i){
        i = get<0>(pivos);
        return;
    }else if( i < get<0>(pivos)){
        int *fimEsq = get<0>(pivos) -1;
        BFPRT(init,i, fimEsq);
    }else if(i > get<1>(pivos)){
        int *inicioDir = get<1>(pivos) + 1;
        BFPRT(inicioDir, i, fin);
    }
}



