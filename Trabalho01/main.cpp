#include <iostream>
#include "QuickSortIndex.h"

//TODO Quicksort with index
//TODO Quicksort with pointers
//TODO Quicksort memory
//TODO Quicksort median of meadians
//TODO Quicksort aleatory pivot
//TODO Function to create aleatory vectors


void PrintVector(int fin, int *vector){
    for (int i = 0; i < fin ; ++i) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int vector[] = {2,9,7,3,5,4,8,1,7};
    int init = 0;
    int fin = 8;
    QuickSortIndex qSortI;
    std::cout << "InitialVector:   ";
    PrintVector(fin, vector);
    qSortI.QuickSort_(init, fin, vector);
    std::cout << "After QuickSort: ";
    PrintVector(fin, vector);

    return 0;
}