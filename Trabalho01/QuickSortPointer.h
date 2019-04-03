//
// Created by fbeze on 01/04/2019.
//

#ifndef TRABALHO01_QUICKSORTPOINTER_H
#define TRABALHO01_QUICKSORTPOINTER_H


class QuickSortPointer{
public:
    QuickSortPointer();
    virtual void QuickSort_(int *init, int *fin);
    void PrintVector_(int* vector, int* fin);
    void Swap_(int *p, int *p_);
    void LomutoPartitioning_ (int *init, int *fin, int *&pivot);
    virtual int* ChoosePivot_(int* first, int* last);

};


#endif //TRABALHO01_QUICKSORTPOINTER_H
