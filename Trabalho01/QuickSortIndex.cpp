//
// Created by fbeze on 01/04/2019.
//
#include "QuickSortIndex.h"
#include <iostream>
using namespace std;

QuickSortIndex::QuickSortIndex() = default;

void QuickSortIndex::QuickSort_(int init, int fin, int *vector) {
    int initR;
    int finL;
    int pivot;

    if (fin <= init){
        return;
    }

    pivot = ChoosePivot_(init, fin);
    pivot = LomutoPartitioning_(init, fin, pivot, vector);

    if(pivot != init || pivot == fin){
        finL = pivot - 1;
        QuickSort_(init, finL, vector);
    }

    if(pivot == init || pivot != fin ){
        initR = pivot + 1;
        QuickSort_(initR, fin, vector);

    }

}

void QuickSortIndex::Swap_(int p, int p_, int vector[]){
    int aux;
    aux = vector[p];
    vector[p] = vector[p_];
    vector[p_] = aux;
}

int QuickSortIndex::ChoosePivot_(int first, int last){
    int pivot = (last + first)/2;
    return pivot;
}

int QuickSortIndex::LomutoPartitioning_ (int init, int fin, int pivot, int vector[]){
    Swap_(init, pivot, vector);

    int i = init;
    int j = i + 1;

    for (; j <= fin; ++j) {
        if(vector[j] < vector[init]){
            i = i + 1;
            Swap_(i,j, vector);
        }
    }
    Swap_(i, init, vector);
    return i;
}

void QuickSortIndex::PrintVector_(int vector[], int fin) {
    for (int i = 0; i <= fin ; ++i) {
        cout << vector[i] << " ";
    }
    cout << endl;
}


