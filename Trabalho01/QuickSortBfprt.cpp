//
// Created by fbeze on 02/04/2019.
//

#include "QuickSortBfprt.h"

QuickSortBfprt::QuickSortBfprt() = default;

tuple<int *, int *> QuickSortBfprt::LomutoTriplePartitioning_(int *init, int *fin, int *&pivot) {
    Swap_(init, pivot);
    int *i = init;
    int *j = init+1;
    int *n = init;
    int p;

    for (j; j <= fin; ++j) {
        if(*j < *init){
            n++;
            p = *n;
            *n = *j;

            i++;
            *j = *i;
            *i = p;
        }

        else if(*j == *init){
            i++;
            Swap_(i,j);
        }
    }
    Swap_(n, init);
    pivot = i;
    return make_tuple(n, i);
}

void QuickSortBfprt::QuickSort_(int *init, int *fin) {
    int *initR;
    int *finL;

    if (fin <= init){
        return;
    }
    int *pivot = ChoosePivot_(init, fin);
    std::tuple<int*, int*> pivots = LomutoTriplePartitioning_(init, fin, pivot);

    if(get<0>(pivots) > init ){
        finL = get<0>(pivots) - 1;
        pivot = finL;
        QuickSort_(init, finL);
    }

    if(get<1>(pivots) < fin ){
        initR = get<1>(pivots) + 1;
        pivot = fin;
        QuickSort_(initR, fin);

    }
}

void QuickSortBfprt::HoareSelection(int *init, int *fin, int *iPivot) {
    int middlePosition = static_cast<int>((fin - init)/sizeof(int));
    int *pivot = init + middlePosition;

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



