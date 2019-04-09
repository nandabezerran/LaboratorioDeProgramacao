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
using namespace std::chrono;

void CopyVector(const int vector[], int vectorAux[], int size){
    for (int i = 0; i < size ; ++i) {
        vectorAux[i] = vector[i];
    }
}

int ChoosePivot_(int first, int last){
    int pivot = (last + first)/2;
    return pivot;
}

void AleatoryVector(int* vector, int size){
    srand((unsigned)time(nullptr));
    for (int i = 0; i < size; ++i) {
        vector[i] = rand() % 100;
    }


}

int main() {
    int size;
    int option = 1;
    int typeEntry;

    QuickSortIndex qSortI;
    QuickSortPointer qSortP;
    QuickSortRandomPivot qSortRp;
    QuickSortBfprt qSortBfprt;
    QuickSortMemory qSortMemory;

    while(option != 0) {
        std::cout << "How do you want your vector?\n 0 - Aleatory Vector\n 1 - Instance generator " << std::endl;
        std::cin >> typeEntry;
        std::cout << "Whats the size of the vector? " << std::endl;
        std::cin >> size;
        int vector[size];
        int vectorAux[size];
        int *initP;
        int *finP;
        int initI;
        int finI;

        if (typeEntry == 0) {
            AleatoryVector(vector, size);

        }

        else if(typeEntry == 1){
            bool aux = escrever_instancia(vector,size);
            if (aux) {
                std::cout << "There's not enough memory " << std::endl;
            }
            else {
                escrever_instancia(vector, size);

            }
        }

        CopyVector(vector, vectorAux, size);
        initP = vectorAux;
        finP = initP + size - 1;

        initI = 0;
        finI = size - 1;

        std::cout << "InitialVector:   ";
        qSortBfprt.PrintVector_(vectorAux, finP);
        std::cout << "\n";


        /*  QUICK SORT INDEX
         *
         */
        CopyVector(vector, vectorAux, size);
        std::cout << "QuickSortIndex:\n";
        auto start = high_resolution_clock::now();
        qSortI.QuickSort_(initI, finI, vectorAux);
        auto stop = high_resolution_clock::now();
        std::cout << "After QuickSort: ";
        qSortI.PrintVector_(vectorAux, finI);

        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by QuickSortIndex: "
             << duration.count() << " microseconds\n" << endl;


        /*  QUICK SORT POINTER
         *
         */
        CopyVector(vector, vectorAux, size);
        std::cout << "QuickSortPointer:\n";
        start = high_resolution_clock::now();
        qSortP.QuickSort_(initP, finP);
        stop = high_resolution_clock::now();
        std::cout << "After QuickSort: ";
        qSortP.PrintVector_(vectorAux, finP);

        duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by QuickSortPointer: "
             << duration.count() << " microseconds\n" << endl;


        /* QUICK SORT RANDOM PIVOT
         *
         */
        CopyVector(vector, vectorAux, size);
        std::cout << "QuickSortRandomPivot:\n";
        start = high_resolution_clock::now();
        qSortRp.QuickSort_(initP, finP);
        stop = high_resolution_clock::now();
        std::cout << "After QuickSort: ";
        qSortRp.PrintVector_(vectorAux, finP);

        duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by QuickSortRandomPivot: "
             << duration.count() << " microseconds\n" << endl;


        /* QUICK SORT MEMORY
         *
         */
        CopyVector(vector, vectorAux, size);
        std::cout << "QuickSortMemory:\n";
        start = high_resolution_clock::now();
        qSortMemory.QuickSort_(initP, finP);
        stop = high_resolution_clock::now();
        std::cout << "After QuickSort: ";
        qSortMemory.PrintVector_(vectorAux, finP);

        duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by QuickSortMemory: "
             << duration.count() << " microseconds\n" << endl;


        /* QUICK SORT BFPRT
         *
         */
        CopyVector(vector, vectorAux, size);
        std::cout << "QuickSortBfprt:\n";
        start = high_resolution_clock::now();
        qSortBfprt.QuickSort_(initP, finP);
        stop = high_resolution_clock::now();
        std::cout << "After QuickSort: ";
        qSortBfprt.PrintVector_(vectorAux, finP);

        duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by QuickSortBfprt: "
             << duration.count() << " microseconds\n" << endl;




        std::cout << "\nDo you want to enter another vector?\n   Press - Any number to continue"
                     "\n   Press - 0 to exit " << std::endl;
        std::cin >> option;

        if(option == 0){
            break;
        }

        free(vector);

    }

}