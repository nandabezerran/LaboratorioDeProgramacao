#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "QuickSortIndex.h"
#include "QuickSortPointer.h"
#include "QuickSortRandomPivot.h"
//TODO Quicksort with index
//TODO Quicksort with pointers
//TODO Quicksort memory
//TODO Quicksort median of meadians
//TODO Quicksort aleatory pivot
//TODO Function to create aleatory vectors


int* AleatoryVector(int* vector, int size){
    srand((unsigned)time(nullptr));
    for (int i = 0; i < size; ++i) {
        vector[i] = rand() % 100;
    }

    return vector;

}

int main() {
    int size;
    std::cout << "Whats the size of the vector? " << std::endl;
    std::cin >> size ;
    int vector[size];
    int *init = AleatoryVector(vector, size);
    int *fin = vector + (size - 1);
    QuickSortIndex qSortI;
    QuickSortPointer qSortP;
    QuickSortRandomPivot qSortRp;
    std::cout << "InitialVector:   ";
    qSortRp.PrintVector_(vector, fin);
    qSortRp.QuickSort_(init, fin);
    std::cout << "After QuickSort: ";
    qSortRp.PrintVector_(vector, fin);

    return 0;
}