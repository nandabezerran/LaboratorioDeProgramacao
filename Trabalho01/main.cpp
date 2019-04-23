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

bool CheckOrdered(int *init, const int* fin){
    bool isOrdened = true;
    while(init < fin){
        if (init > init + 1){
            isOrdened = false;
        }
        init++;
    }
    return isOrdened;
}

void CopyVector(const int vector[], int vectorAux[], int size){
    for (int i = 0; i < size ; ++i) {
        vectorAux[i] = vector[i];
    }
}

int ChoosePivot(int first, int last){
    int pivot = (last + first)/2;
    return pivot;
}

void AleatoryVector(int* vector, int size, int range){
    srand((unsigned)time(nullptr));
    for (int i = 0; i < size; ++i) {
        vector[i] = rand() % range;
    }

}

int main() {
    int size; // Size of the vector;
    int option = 1;// Variable to receive the option of the user, if he want to continue or not in the loop;
    int typeEntry; // Variable to keep the type of generation of the vector;
    int isOrdered;
    int range;

    // Every type of quick sort is a class. So here we instantiate all the types;
    QuickSortIndex qSortI;
    QuickSortPointer qSortP;
    QuickSortRandomPivot qSortRp;
    QuickSortBfprt qSortBfprt;
    QuickSortMemory qSortMemory;

    // In this loop we receive from de user the how he want the vector to be generated and the size of it. We will show
    // the results of all quick sort and the time they took to compute. At the end we ask if the user want to continue
    // in the loop;
    while(option != 0) {
        std::cout << "How do you want your vector?\n0 - Aleatory Vector\n1 - Instance Generator " << std::endl;
        std::cin >> typeEntry;

        std::cout << "What's the range of the aleatory numbers?\n" << std::endl;
        std::cin >> range;

        if (typeEntry != 0 && typeEntry != 1) {
            std::cout << "Wrong type of entry. " << std::endl;
        }

        else {
            std::cout << "Whats the size of the vector? " << std::endl;
            std::cin >> size;
            int vector[size]; // Original vector;
            int vectorAux[size]; // Auxiliar vector to copy the original into it;
            int *initP; // Pointer for the first element of the vector;
            int *finP;  // Pointer for the last element of the vector;

            int initI; // Index of the first element of the vector;
            int finI;  // Index of the last element of the vector;

            // Using the aleatory generator;
            if (typeEntry == 0) {
                AleatoryVector(vector, size, range);

            }

            // Using the file to write bad instances;
            else if (typeEntry == 1) {
                bool aux = escrever_instancia(vector, size);
                if (aux) {
                    std::cout << "There's not enough memory " << std::endl;
                } else {
                    escrever_instancia(vector, size);

                }
            }


            CopyVector(vector, vectorAux, size); // Copy the vector to don't modify the original vector;
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
            auto start = high_resolution_clock::now(); // Starts the clock;
            qSortI.QuickSort_(initI, finI, vectorAux);
            auto stop = high_resolution_clock::now(); // Stops the clock;
            std::cout << "After QuickSort: ";

            isOrdered = CheckOrdered(initP, finP);
            if(isOrdered){
                std::cout << "Vector is ordered\n" << std::endl;
            }
            else{
                std::cout << "Vector is ordered\n" << std::endl;
            }

            //qSortI.PrintVector_(vectorAux, finI);

            auto duration = duration_cast<microseconds>(stop - start); // Compute the duration of the function;
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

            isOrdered = CheckOrdered(initP, finP);
            if(isOrdered){
                std::cout << "Vector is ordered\n" << std::endl;
            }
            else{
                std::cout << "Vector is ordered\n" << std::endl;
            }

            //qSortP.PrintVector_(vectorAux, finP);

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

            isOrdered = CheckOrdered(initP, finP);
            if(isOrdered){
                std::cout << "Vector is ordered\n" << std::endl;
            }
            else{
                std::cout << "Vector is ordered\n" << std::endl;
            }

            //qSortRp.PrintVector_(vectorAux, finP);

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

            isOrdered = CheckOrdered(initP, finP);
            if(isOrdered){
                std::cout << "Vector is ordered\n" << std::endl;
            }
            else{
                std::cout << "Vector is ordered\n" << std::endl;
            }

            //qSortMemory.PrintVector_(vectorAux, finP);

            duration = duration_cast<microseconds>(stop - start);
            cout << "Time taken by QuickSortMemory: "
                 << duration.count() << " microseconds\n" << endl;


            /* QUICK SORT BFPRT_
             *
             */
            CopyVector(vector, vectorAux, size);
            std::cout << "QuickSortBfprt:\n";
            start = high_resolution_clock::now();
            qSortBfprt.QuickSort_(initP, finP);
            stop = high_resolution_clock::now();
            std::cout << "After QuickSort: ";

            isOrdered = CheckOrdered(initP, finP);
            if(isOrdered){
                std::cout << "Vector is ordered\n" << std::endl;
            }
            else{
                std::cout << "Vector is ordered\n" << std::endl;
            }
            //qSortBfprt.PrintVector_(vectorAux, finP);

            duration = duration_cast<microseconds>(stop - start);
            cout << "Time taken by QuickSortBfprt: "
                 << duration.count() << " microseconds\n" << endl;

            free(vector);
            free(vectorAux);
        }

        std::cout << "\nDo you want to enter another vector?\n   Press - Any number to continue"
                     "\n   Press - 0 to exit " << std::endl;
        std::cin >> option;


        if(option == 0){
            break;
        }

    }

}