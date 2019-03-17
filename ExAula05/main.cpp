#include <iostream>

void Swap(int *p, int *p_){
    int aux;
    aux = *p;
    *p = *p_;
    *p_ = aux;
}

int* LomutoPartitioning (int *init, int *fin){
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
    std::cout << "Pivot: " << *pivot << std::endl;
    return pivot;


}

void PrintVector(int *vector){
    for (int i = 0; i < 9 ; ++i) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}


void QuickSortWithoutTailRecursion(int *init, int *fin){
    int *pivot;
    while (init <= fin){
        pivot = LomutoPartitioning(init, fin);

        QuickSortWithoutTailRecursion(init, pivot -1);

        init = pivot + 1;
    }
}
int main() {
    int vector[] = {2,9,6,3,5,4,8,1,7};
    int *init = vector;
    int *fin = vector + 8;
    int *pivot = vector + 4;

    std::cout << "InitialVector:   ";
    PrintVector(vector);
    QuickSortWithoutTailRecursion(init, fin);
    std::cout << "After QuickSort: ";
    PrintVector(vector);

    return 0;
}