#include <iostream>
using namespace std;
#include<tuple>

void Swap(int *p, int *p_){
    int aux;
    aux = *p;
    *p = *p_;
    *p_ = aux;
}

tuple<int*, int*> LomutoPartitioningWithTriplePartitioning (int *init, int *fin, int *&pivot){
    Swap(init, pivot);
    int *i = init;
    int *j = init+1;
    int *n = init;
    int p;

    for (j; j <= fin; ++j) {
        if(*j < *init){
            n++;
            p = *n;
            *n = *j;

            i++;
            *j = *i;
            *i = p;
        }

        else if(*j == *init){
            i++;
            Swap(i,j);
        }
    }
    Swap(n, init);
    pivot = i;
    return make_tuple(n, i);
}

void PrintVector(int *vector){
    for (int i = 0; i < 10 ; ++i) {
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

    std::tuple<int*, int*> pivots = LomutoPartitioningWithTriplePartitioning(init, fin, pivot);

    if(get<0>(pivots) > init ){
        finL = get<0>(pivots) - 1;
        pivot = finL;
        QuickSort(init, finL, pivot);
    }

    if(get<1>(pivots) < fin ){
        initR = get<1>(pivots) + 1;
        pivot = fin;
        QuickSort(initR, fin, pivot);

    }
}
int main() {
    int vector[] = {10, 2, 6, 8, 6 , 6, 3, 4, 6, 5};
    int *init = vector;
    int *fin = vector + 9;
    int *pivot = vector + 4;

    std::cout << "Pivot: " << *pivot << std::endl;
    std::cout << "InitialVector:   ";
    PrintVector(vector);
    QuickSort(init, fin, pivot);
    std::cout << "After QuickSort: ";
    PrintVector(vector);

    return 0;
}