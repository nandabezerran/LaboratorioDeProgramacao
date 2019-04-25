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
    int goThroughPattern = 0;      // It counts in which index we are in the pattern;
    int    goThroughText = 0;      // It counts in which index we are in the text;

    while(*pText != '\0'){
        if(*pText == *pPattern){
            pPattern = pPattern + 1;
            goThroughPattern++;
        }

        else{
            pPattern = pPattern - goThroughPattern;
        }

        if(*pPattern == '\0'){
            pPattern = pPattern - goThroughPattern;
            *pResult = goThroughText - goThroughPattern;
            pResult = pResult + 1;
            goThroughPattern = 0;
        }

        pText = pText + 1;
        goThroughText++;

    }
    *pResult = -1;
}
int* computationOfPi(const char* pPattern, int* pPiVector){
    int k;
    int lenght;
    *pPiVector = 0;
    for (int i = 1; *(pPattern + i) != '\0' ; ++i) {
        k = i - 1;
        for(;;){
            lenght = *(pPiVector + k);
            if (lenght == 0) {
                if (*pPattern == *(pPattern + i)) {
                    *(pPiVector + i) = 1;
                    break;
                } else {
                    *(pPiVector + i) = 0;
                    break;
                }
            } else {
                if (*(pPattern + i) == *(pPattern + lenght)) {
                    *(pPiVector + i) = lenght + 1;
                    break;
                } else {
                    k = lenght - 1;
                }
            }
        }
    }
    return pPiVector;
}

void knuthMorrisPratt(const char* pText, const char* pPattern, int *pResult){
    int *piVector =  new int[sizeof(pPattern)]();
    computationOfPi(pPattern, piVector);
    int goThroughText = 0;
    int goThroughPattern = 0;
    while(*(pText + goThroughText) != '\0'){
        if(*(pText + goThroughText) != *(pPattern + goThroughPattern)){
            if(goThroughPattern == 0){
                goThroughText++;
            }
            else{
                goThroughPattern = *(piVector + goThroughPattern - 1);
            }
        }
        else{
            if(*(pPattern + goThroughPattern) == '\0' ){
                *pResult = goThroughText - goThroughPattern;
                pResult = pResult + 1;
                goThroughPattern = *(piVector + goThroughPattern);
                goThroughText++;
            }
            else{
                goThroughText++;
                goThroughPattern++;
            }
        }
    }
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

    knuthMorrisPratt(text,pattern,result);
    printVector(result);

    return 0;
}