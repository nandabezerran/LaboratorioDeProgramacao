#include <iostream>

void Swap(int *p, int *p_){
    int aux;
    aux = *p;
    *p = *p_;
    *p_ = aux;
}
void LomutoPartitioning (int *init, int *fin, int *pivot){
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

}

void PrintVector(int* vector){
    for (int i = 0; i < 9 ; ++i) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int vector[9] = {2,9,7,3,5,4,8,1,7};
    int *init = vector;
    int *fin = vector + 8;
    int *pivot = vector + 4;

    std::cout << "Pivot: " << *pivot << std::endl;
    LomutoPartitioning(init, fin, pivot);
    PrintVector(vector);

    return 0;
}

