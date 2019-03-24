#include <iostream>
#define vectorSize = 9;
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

void QuickSort(int *init, int *fin, int *pivot){
    int *initR;
    int *finL;

    if (fin <= init){
        return;
    }

    HoareSelection(init, fin, pivot);

    if(pivot != init || pivot == fin){
        finL = pivot - 1;
        pivot = finL;
        QuickSort(init, finL, pivot);
    }

    if(pivot == init || pivot != fin ){
        initR = pivot + 1;
        pivot = fin;
        QuickSort(initR, fin, pivot);

    }
}

void PrintVector(int *vector){
    for (int i = 0; i < 9 ; ++i) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int vector[] = {2,9,6,3,5,4,8,1,7};
    int *init = vector;
    int *fin = vector + 8;
    int *iPivot = vector + 4;
    std::cout << "InitialVector:   ";
    PrintVector(vector);
    QuickSort(init, fin, iPivot);
    std::cout << "After QuickSort:   ";
    PrintVector(vector);

    return 0;
}