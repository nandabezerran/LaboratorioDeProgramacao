#include <iostream>

void Swap(int *p, int *p_){
    int aux;
    aux = *p;
    *p = *p_;
    *p_ = aux;
}

void HoareSelection (int *init, int *fin, int *iPivot){
    int middlePosition = static_cast<int>((fin - init)/sizeof(int));
    int *pivot = init + middlePosition;

    Swap(init, pivot);

    int *i = init;
    int *j = i + 1;

    for (j; j <= fin; ++j) {
        if(*j < *init){
            i = i + 1;
            Swap(i,j);
        }
    }
    Swap(i, init);
    pivot = i;

    if (iPivot == pivot){
        return;
    }

    if (iPivot < pivot){
        HoareSelection(init, pivot-1, iPivot);
    }

    else{
        HoareSelection(pivot + 1, fin, iPivot);
    }

}

int* BFPRT(int *init, int *fin, int vectorSize, int *pivot){
    int qtdOfPartitions = vectorSize/5 + (vectorSize % 5 != 0);
    int medians[qtdOfPartitions];
    int *auxInit = init;
    int *auxFin = init + 4;
    int *middle;

    for (int i = 0; i < qtdOfPartitions; ++i) {
        if((auxInit + 5) >= fin){
            middle = auxInit + ((fin - auxInit)/2);
            HoareSelection(auxInit, fin, middle);
            medians[i] = *middle;
        }
        else{
            middle = auxInit + ((auxFin - auxInit)/2);
            HoareSelection(auxInit, auxFin, middle);
            medians[i] = *middle;
        }
        auxInit = auxInit + 5;
        auxFin = auxFin + 5;
    }
    pivot = medians + qtdOfPartitions/2;
    HoareSelection(medians, medians + qtdOfPartitions, pivot);
    return pivot;

}

void QuickSort(int *init, int *fin, int *pivot, int vectorSize){
    int *initR;
    int *finL;

    if (fin <= init){
        return;
    }

    BFPRT(init, fin, vectorSize, pivot);

    if(pivot != init || pivot == fin){
        finL = pivot - 1;
        pivot = finL;
        QuickSort(init, finL, pivot, vectorSize);
    }

    if(pivot == init || pivot != fin ){
        initR = pivot + 1;
        pivot = fin;
        QuickSort(initR, fin, pivot, vectorSize);

    }
}

void PrintVector(int *vector){
    for (int i = 0; i < 8 ; ++i) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int* pivot;
    int vector[] = {6, 5, 8, 2, 4, 1, 7, 3};
    int vectorSize = 8;
    int *init = vector;
    int *fin = vector + 7 ;
    BFPRT(init, fin, vectorSize, pivot);
    PrintVector(vector);
    return 0;
}