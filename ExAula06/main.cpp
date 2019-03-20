#include <iostream>

void Swap(int *p, int *p_){
    int aux;
    aux = *p;
    *p = *p_;
    *p_ = aux;
}

void LomutoPartitioning (int *init, int *fin, int *&pivot){
    Swap(init, pivot);

    int *i = init;
    int *j = init + 1;
    int *n = init;
    int *p;


    for (j; j <= fin; ++j) {
        if(*j < *init){
            i = i + 1;
            *p = *i;
            *i =*j;

            n = n+1;

            *j = *j;
            *n = *p;
        }

        if(*j == *init){
            n = n + 1;
            Swap(n,j);
        }
    }
    Swap(i, init);
    pivot = i;
}

void PrintVector(int *vector){
    for (int i = 0; i < 9 ; ++i) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

void QuickSort(int *init, int *fin, int *pivot){
    int *initR;
    int *finL;

    if (fin <= init){
        return;
    }

    LomutoPartitioning(init, fin, pivot);

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
int main() {
    int vector[] = {2,9,7,3,5,4,8,1,7};
    int *init = vector;
    int *fin = vector + 8;
    int *pivot = vector + 4;

    std::cout << "Pivot: " << *pivot << std::endl;
    std::cout << "InitialVector:   ";
    PrintVector(vector);
    QuickSort(init, fin, pivot);
    std::cout << "After QuickSort: ";
    PrintVector(vector);

    return 0;
}