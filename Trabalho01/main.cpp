#include <iostream>
#include "QuickSortIndex.h"
#include "QuickSortPointer.h"

//TODO Quicksort with index
//TODO Quicksort with pointers
//TODO Quicksort memory
//TODO Quicksort median of meadians
//TODO Quicksort aleatory pivot
//TODO Function to create aleatory vectors




int main() {
    int vector[] = {2,9,7,3,5,4,8,1,7};
    int *init = vector;
    int *fin = vector + 8;
    QuickSortIndex qSortI;
    QuickSortPointer qSortP;
    std::cout << "InitialVector:   ";
    qSortP.PrintVector_(vector, fin);
    qSortP.QuickSort_(init, fin);
    std::cout << "After QuickSort: ";
    qSortP.PrintVector_(vector, fin);

    return 0;
}