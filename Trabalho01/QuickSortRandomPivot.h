//
// Created by fbeze on 01/04/2019.
//

#ifndef TRABALHO01_QUICKSORTRANDOMPIVOT_H
#define TRABALHO01_QUICKSORTRANDOMPIVOT_H
#include "QuickSortPointer.h"

class QuickSortRandomPivot : public QuickSortPointer {
public:
    QuickSortRandomPivot();
    int* ChoosePivot_(int* first, int* last) override;
};


#endif //TRABALHO01_QUICKSORTRANDOMPIVOT_H
