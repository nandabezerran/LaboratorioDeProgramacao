//
// Created by fbeze on 01/04/2019.
//

#include "QuickSortIndex.h"

QuickSortIndex::QuickSortIndex() = default;

void QuickSortIndex::QuickSort_(int init, int fin, int *vector) {

    int initR;
    int finL;
    int pivot;

    if (fin <= init){
        return;
    }

    pivot = ChoosePivot_(init, fin);
    LomutoPartitioning_(init, fin, pivot, vector);

    if(pivot != init || pivot == fin){
        finL = pivot - 1;
        QuickSort_(init, finL, vector);
    }

    if(pivot == init || pivot != fin ){
        initR = pivot + 1;
        QuickSort_(initR, fin, vector);

    }

}


