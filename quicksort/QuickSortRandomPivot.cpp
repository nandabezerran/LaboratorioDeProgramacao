//
// Created by fbeze on 01/04/2019.
//
#include <stdlib.h>
#include "QuickSortRandomPivot.h"
#include <iostream>
#include <time.h>

using namespace std;


QuickSortRandomPivot::QuickSortRandomPivot() = default;

int* QuickSortRandomPivot::ChoosePivot_(int* first, int* last){
    srand((unsigned)time(nullptr));
    int *aux = first + (rand() % (last - first + 1));
    int *pivot = aux;
    return pivot;
}