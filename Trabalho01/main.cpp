#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include "QuickSortIndex.h"
#include "QuickSortPointer.h"
#include "QuickSortRandomPivot.h"
#include "QuickSortBfprt.h"
#include "QuickSortMemory.h"
using namespace std::chrono;
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
    int option = 1;
    QuickSortIndex qSortI;
    QuickSortPointer qSortP;
    QuickSortRandomPivot qSortRp;
    QuickSortBfprt qSortBfprt;
    QuickSortMemory qSortMemory;

    while(option != 0) {
        std::cout << "Whats the size of the vector? " << std::endl;
        std::cin >> size;
        int vector[size];
        int *init = AleatoryVector(vector, size);
        int *fin = vector + (size - 1);

        std::cout << "InitialVector:   ";
        qSortMemory.PrintVector_(vector, fin);
        auto start = high_resolution_clock::now();
        qSortMemory.QuickSort_(init, fin);
        auto stop = high_resolution_clock::now();
        std::cout << "After QuickSort: ";
        qSortMemory.PrintVector_(vector, fin);

        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by function: "
             << duration.count() << " microseconds" << endl;

        std::cout << "\nDo you want to enter another vector?\n   Press - Any number to continue"
                     "\n   Press - 0 to exit " << std::endl;
        std::cin >> option;
        if(option == 0){
            break;
        }

        free(vector);
        delete init;
        delete fin;

    }

}