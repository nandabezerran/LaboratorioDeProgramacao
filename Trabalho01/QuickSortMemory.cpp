//
// Created by fbeze on 03/04/2019.
//

#include "QuickSortMemory.h"

void QuickSortMemory::QuickSort_(int *init, int *fin){
    int *pivot;
    while (init <= fin){
        pivot = ChoosePivot_(init, fin);
        LomutoPartitioning_(init, fin, pivot);

        if((pivot - init) > (fin - pivot)) {
            QuickSort_(init, pivot - 1);
            init = pivot + 1;
        }
        else{
            QuickSort_(pivot + 1, fin);
            fin = pivot - 1;
        }

    }
}


QuickSortMemory::QuickSortMemory() = default;
