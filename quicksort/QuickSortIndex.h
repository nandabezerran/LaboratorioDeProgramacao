//
// Created by fbeze on 01/04/2019.
//

#ifndef TRABALHO01_QUICKSORTINDEX_H
#define TRABALHO01_QUICKSORTINDEX_H


class QuickSortIndex {
public:
    QuickSortIndex();
    void QuickSort_(int init, int fin, int vector[]) ;
    void PrintVector_(int vector[], int fin);
    void Swap_(int p, int p_, int vector[]);
    int LomutoPartitioning_ (int init, int fin, int pivot, int vector[]);

};


#endif //TRABALHO01_QUICKSORTINDEX_H
