//
// Created by fbeze on 01/04/2019.
//

#ifndef TRABALHO01_QUICKSORTCHOOSINGPIVOT_H
#define TRABALHO01_QUICKSORTCHOOSINGPIVOT_H


class QuickSortChoosingPivot {
public:
    void Swap_(int p, int p_, int vector[]);
    int LomutoPartitioning_ (int init, int fin, int pivot, int vector[]);
    int ChoosePivot_(int first, int last) ;
    virtual void QuickSort_(int init, int fin, int vector[]) = 0;

};



#endif //TRABALHO01_QUICKSORTCHOOSINGPIVOT_H
