#include <iostream>

void Swap(int *p, int *p_){
    int aux;
    aux = *p;
    *p = *p_;
    *p_ = aux;
}

int* LomutoPartitioning (int *init, int *fin){
    int *pivot = init + ((fin - init)/2);
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

    pivot = LomutoPartitioning(init, fin);
    if(pivot != init || pivot == fin){
        QuickSortWithoutTailRecursion(init, pivot - 1);
    }

    if(pivot == init || pivot != fin ){
        for (int *j = pivot+1; j <= fin; j++ ){
            for (int *i = pivot+1; i <= fin ; i++) {
                if(*j < *i){
                    Swap(j,i);
                }
            }
        }

    }
}
int main() {
    int vector[] = {2,9,6,3,5,4,8,1,7};
    int *init = vector;
    int *fin = vector + 8;

    std::cout << "InitialVector:   ";
    PrintVector(vector);
    QuickSortWithoutTailRecursion(init, fin);
    std::cout << "After QuickSort: ";
    PrintVector(vector);

    return 0;
}