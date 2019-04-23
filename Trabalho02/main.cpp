#include <iostream>
#include <string.h>

void printVector(const int* vector){
    while(*vector != -1){
        std::cout << *vector << " ";
        vector = vector + 1;
    }
    std::cout << std::endl;
}

void bruteForceAlgorithm(const char* pText, const char* pPattern, int *pResult){
    int cont = 0;      // It counts in which index we are in the pattern;
    int goThrough = 0; // It counts in which index we are in the text;
    while(*pText != '\0'){
        if(*pText == *pPattern){
            pPattern = pPattern + 1;
            cont++;
        }

        else{
            pPattern = pPattern - cont;
        }

        if(*pPattern == '\0'){
            pPattern = pPattern - cont;
            *pResult = goThrough - cont;
            pResult = pResult + 1;
            cont = 0;
        }

        pText = pText + 1;
        goThrough++;

    }
    *pResult = -1;
}

int main() {
//    int textSize;
//    int patternSize;
    int *result = new int[sizeof("o celito e o amor da minha vidda")]();

//    std::cout << "Please, enter the size of the text " << std::endl;
//    std::cin >> textSize;
//    std::cout << "Please, enter the size of the pattern " << std::endl;
//    std::cin >> patternSize;

    char *text = new char[sizeof("o celito é o amor da minha vidda")]();
    strcpy(text, "o celito é o amor da minha vidda");
    char *pattern = new char[sizeof("a")]();
    strcpy(pattern, "a");

    bruteForceAlgorithm(text,pattern,result);

    printVector(result);

    return 0;
}