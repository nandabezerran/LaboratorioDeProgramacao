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
#include "instancias_ruins_Quicksort.hpp"

int ChoosePivot_(int first, int last){
    int pivot = (last + first)/2;
    return pivot;
}

using namespace std::chrono;

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
        bool aux = false; //= escrever_instancia(vector,size);
        if (aux) {
            std::cout << "There's not enough memory " << std::endl;
        }
        else {
            int* init = AleatoryVector(vector, size);
            int* fin = init + size - 1;

            std::cout << "InitialVector:   ";
            qSortBfprt.PrintVector_(vector, fin);
            auto start = high_resolution_clock::now();
            qSortBfprt.QuickSort_(init, fin);
            auto stop = high_resolution_clock::now();
            std::cout << "After QuickSort: ";
            qSortBfprt.PrintVector_(vector, fin);

            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Time taken by function: "
                 << duration.count() << " microseconds" << endl;

            //delete init;
            //delete fin;
        }
        std::cout << "\nDo you want to enter another vector?\n   Press - Any number to continue"
                     "\n   Press - 0 to exit " << std::endl;
        std::cin >> option;
        if(option == 0){
            break;
        }

        free(vector);

    }

}