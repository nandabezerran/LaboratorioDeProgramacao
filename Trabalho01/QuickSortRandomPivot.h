//
// Created by fbeze on 01/04/2019.
//

#ifndef TRABALHO01_QUICKSORTRANDOMPIVOT_H
#define TRABALHO01_QUICKSORTRANDOMPIVOT_H


class QuickSortRandomPivot {
public:
    QuickSortRandomPivot();
    void QuickSort_(int *init, int *fin);
    void PrintVector_(int* vector, int* fin);
    void Swap_(int *p, int *p_);
    void LomutoPartitioning_ (int *init, int *fin, int *&pivot);
    int* ChoosePivot_(int* first, int* last) ;
};


#endif //TRABALHO01_QUICKSORTRANDOMPIVOT_H
