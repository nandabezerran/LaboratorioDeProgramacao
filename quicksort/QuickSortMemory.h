//
// Created by fbeze on 03/04/2019.
//

#ifndef TRABALHO01_QUICKSORTMEMORY_H
#define TRABALHO01_QUICKSORTMEMORY_H


#include "QuickSortPointer.h"

class QuickSortMemory : public QuickSortPointer{
public:
    QuickSortMemory();

    void QuickSort_(int *init, int *fin) override;
};


#endif //TRABALHO01_QUICKSORTMEMORY_H
