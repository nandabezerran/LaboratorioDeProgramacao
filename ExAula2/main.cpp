#include <iostream>

bool sao_iguais(const char *r, const char *s){
    while(*s != '\0' || *r != '\0'){
        if (*s == *r){
            s = s +1;
            r = r +1;
        }
        else{
            return false;
        }
    }
    return true;
}

void inverter(int *v, int n){
    int *auxiliar_vector = (int*) malloc(6 * sizeof(int));
    for (int i = 0; i < n; ++i) {
        *auxiliar_vector = *v;
        v = v + 1;
        auxiliar_vector = auxiliar_vector + 1;
    }
    v = v - 1;
    auxiliar_vector = auxiliar_vector - n;
    for (int i = 0; i < n; ++i) {
        *v = *auxiliar_vector;
        v = v - 1;
        auxiliar_vector = auxiliar_vector + 1;
    }
}

int main() {
//    char *r = "abcd";
//    char *s = "abcde";
//    bool result = sao_iguais(r,s);
//
    int vector[6] = {1, 2, 3, 4, 5, 6};
    int *v = vector;
    int n = 6;
    inverter(v,n);

    for (int i=0; i<n; i++) {
        std::cout << *v << ", ";
        v = v + 1;
    }
    return 0;
    return 0;
}