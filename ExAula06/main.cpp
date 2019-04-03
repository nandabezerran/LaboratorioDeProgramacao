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
    int *m = init;

    for (; j <= fin; ++j) {
        if(*j < *init){
            i++;
            Swap(i,j);

            m++;
            Swap(m,i);

        }

        else if(*j == *init){
            i++;
            Swap(i,j);
        }
    }
    Swap(m, init);
    pivot = i;
    return make_tuple(m, i);
}

void PrintVector(int *vector){
    for (int i = 0; i < 15 ; ++i) {
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
    int vector[] = {1, 2, 5, 2, 4, 20, 1, 3, 6, 5, 5, 4, 1, 2, 1};
    int *init = vector;
    int *fin = vector + 14;
    int *pivot = vector + 4;

    std::cout << "Pivot: " << *pivot << std::endl;
    std::cout << "InitialVector:   ";
    PrintVector(vector);
    QuickSort(init, fin, pivot);
    std::cout << "After QuickSort: ";
    PrintVector(vector);

    return 0;
}