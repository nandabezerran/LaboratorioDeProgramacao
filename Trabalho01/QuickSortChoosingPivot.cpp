//
// Created by fbeze on 01/04/2019.
//

#include "QuickSortChoosingPivot.h"
void QuickSortChoosingPivot::Swap_(int p, int p_, int vector[]){
    int aux;
    aux = vector[p];
    vector[p] = vector[p_];
    vector[p_] = aux;
}

int QuickSortChoosingPivot::ChoosePivot_(int first, int last){
    int pivot = (last - first)/2;
    return pivot;
}

void QuickSortChoosingPivot::LomutoPartitioning_ (int init, int fin, int pivot, int vector[]){
    Swap_(init, pivot, vector);

    int i = init;
    int j = i + 1;

    for (; vector[j] <= vector[fin]; ++j) {
        if(vector[j] < vector[init]){
            i = i + 1;
            Swap_(i,j, vector);
        }
    }
    Swap_(i, init, vector);
}