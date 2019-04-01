//
// Created by fbeze on 01/04/2019.
//

#ifndef TRABALHO01_QUICKSORTINDEX_H
#define TRABALHO01_QUICKSORTINDEX_H

#include "QuickSortChoosingPivot.h"

class QuickSortIndex : public QuickSortChoosingPivot {
public:
    QuickSortIndex();
    void QuickSort_(int init, int fin, int vector[]) override;

};


#endif //TRABALHO01_QUICKSORTINDEX_H
