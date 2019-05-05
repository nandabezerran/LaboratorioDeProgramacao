#include <iostream>
#include <string.h>
#include "instancias_Reais_Trabalho_2.hpp"
#include <time.h>

void generateVectorA(char* pVector, int pSize, int b){
    for (int i = 0; i < pSize - 1; ++i) {
        pVector[i] = 'a';
    }
    if (b == 1){
        pVector[pSize - 1] = 'b';
        pVector[pSize] = '\0';
    }
    else {
        pVector[pSize - 1] = '\0';
    }
}

void aleatoryVector(char* vector, int size, int range){
    char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                       'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    for (int i = 0; i < size - 1; ++i) {
        vector[i] = alphabet[rand() % range];
    }
    vector[size-1] = '\0';

}

/* Print to the user the result vector
 * @param vector the vector we want to print
 */
void printResultVector(const int *vector){
    int elements = 0;
    while(*vector != -1){
        vector = vector + 1;
        elements++;
    }
    std::cout << elements << std::endl;
}

/* Print a char vector
 * @param vector the vector we want to print
 */
void printCharVector(const char *vector){
    while(*vector != '\0'){
        std::cout << *vector;
        vector = vector + 1;
    }
    std::cout << std::endl;
}

/* Searches using a brute force way subsequences in the text which are equal to the pattern. Then fill up the pResult
 * vector with the index in which those subsequences starts. When there is no more ocurrencies the last item of the vector is a
 * -1 to indicate the end of the content, because the pResult may be bigger than its content.
 * @param pText the text in which we want to search the subsequences
 * @param pPattern pattern we want to search in the text.
 * @param pResult vector that will be filled up with the index in which those subsequences starts.
 */
void bruteForceAlgorithm(const char* pText, const char* pPattern, int *pResult){
    int goThroughPattern = 0;      // It counts in which index we are in the pattern;
    const char *goThroughText = pText;      // It counts in which index we are in the text;

    while(*goThroughText != '\0'){
        if(*goThroughText == *pPattern){
            const char *match = goThroughText + 1;
            const char *patternAux = pPattern + 1;
            while(*match == *patternAux && *patternAux != '\0') {
                match++;
                patternAux++;
            }
            if(*patternAux == '\0') {
                *pResult = (int) (goThroughText - pText);
                pResult++;
            }
        }
        goThroughText++;
    }

    *pResult = -1;
}

/* Calculates the vector pPiVector, where pPiVector[j] is the length of the longest proper prefix of the pattern
 * pPattern[0 ... j] which is also a suffix of this pattern.
 * @param pPattern the pattern you want to search the ocurrencies in the text
 * @param pPiVector the vector to be filled with the size of the longest prefix in every pPattern[0 ... j]
 */
void computationOfPi(const char* pPattern, int* pPiVector){
    int k;
    int length;
    *pPiVector = 0;
    for (int i = 1; pPattern[i] != '\0' ; ++i) {
        k = i - 1;
        for(;;){
            length = pPiVector[k];
            if (length == 0) {
                if (pPattern[0] == pPattern[i]) {
                    pPiVector[i] = 1;
                    break;
                } else {
                    pPiVector[i] = 0;
                    break;
                }
            } else {
                if (pPattern[i] == pPattern[length]) {
                    pPiVector[i] = length + 1;
                    break;
                } else {
                    k = length - 1;
                }
            }
        }
    }
}

/* Searches using the technique of Knuth Morris Pratt subsequences in the text which are equal to the pattern.
 * Then fill up the pResult vector with the index in which those subsequences starts.
 * When there is no more ocurrencies the last item of the vector is a -1 to indicate the end of the content, because
 * the pResult may be bigger than its content.
 * @param pText the text in which we want to search the subsequences
 * @param pPattern pattern we want to search in the text.
 * @param pResult vector that will be filled up with the index in which those subsequences starts.
 */
void knuthMorrisPratt(const char* pText, const char* pPattern, int *pResult){
    int *piVector =  new int[sizeof(pPattern)]();
    int goThroughText = 0;
    int goThroughPattern = 0;

    computationOfPi(pPattern, piVector);

    while(pText[goThroughText] != '\0'){
        if(pText[goThroughText] != pPattern[goThroughPattern]){
            if(goThroughPattern == 0){
                goThroughText++;
            }
            else{
                goThroughPattern = piVector[goThroughPattern - 1];
            }
        }
        else{
            if(pPattern[goThroughPattern + 1] == '\0' ){
                *pResult = goThroughText - goThroughPattern;
                pResult = pResult + 1;
                goThroughPattern = piVector[goThroughPattern];
                goThroughText++;
            }
            else{
                goThroughText++;
                goThroughPattern++;
            }
        }
    }

    *pResult = -1;
    free(piVector);

}

bool checkEquality(int* pResultBrute, int* pResultKnuth){
    bool flag = true;
    while(*pResultBrute != -1 && *pResultKnuth != -1){
        if(*pResultBrute != *pResultKnuth){
            flag = false;
        }
        pResultBrute++;
        pResultKnuth++;
    }
    return flag;
}

int main() {
    //TODO instancias aleatorias
    //TODO instancias reais
    //TODO pior caso 1
    //TODO pior caso 2

    srand((unsigned)clock()); // To generate the aleatory vectors;

    int instancesOp;
    int indexRealPattern;
    int textSize;
    int patternSize;
    int firstLetters;
    int op = 1;
    bool eqResultVectors;

    while(op == 1) {
        std::cout << "Please, enter the what kind of instances generator you want\n >>> 1 - Random\n >>> 2 -"
                     " Real\n >>> 3 - Worst Case #1\n >>> 4 - Worst Case #2" << std::endl;
        std::cin >> instancesOp;

        if (instancesOp == 1) {
            std::cout << "Please, enter the size of the text" << std::endl;
            std::cin >> textSize;
            std::cout << "Please, enter the size of the pattern" << std::endl;
            std::cin >> patternSize;
            std::cout << "Please, enter your L, a number between 0 ... 26. (L firts leters of the alphabet)"
                      << std::endl;
            std::cin >> firstLetters;

            char *text = new char[textSize + 1];
            char *pattern = new char[patternSize + 1];
            int *resultBrute = new int[textSize];
            int *resultKnuth = new int[textSize];

            aleatoryVector(text, textSize + 1, firstLetters);
            aleatoryVector(pattern, patternSize + 1, firstLetters);

            printCharVector(text);
            printCharVector(pattern);

            bruteForceAlgorithm(text, pattern, resultBrute);
            printResultVector(resultBrute);
            std::cout << "----------------------------------------"<< std::endl;
            knuthMorrisPratt(text, pattern, resultKnuth);
            printResultVector(resultKnuth);

            eqResultVectors = checkEquality(resultBrute, resultKnuth);

            if(!eqResultVectors){
                std::cout << "The result vectors aren't equal" << std::endl;
            }
            else{
                std::cout << "The result vectors are equal" << std::endl;
            }

            delete[] text;
            delete[] pattern;
            delete[] resultBrute;
            delete[] resultKnuth;
        }

        if (instancesOp == 2) {
            std::cout << "Please, enter the index of the Pattern, its a number between 0 ... 35129" << std::endl;
            std::cin >> indexRealPattern;
            std::cout << "The pattern you choose: ";
            std::cout << Padroes_Palavras[indexRealPattern] << std::endl;

            int *resultBrute = new int[sizeof(Padroes_Palavras)]();
            int *resultKnuth = new int[sizeof(Padroes_Palavras)]();

            bruteForceAlgorithm(Texto_Livros, Padroes_Palavras[indexRealPattern], resultBrute);
            printResultVector(resultBrute);

            knuthMorrisPratt(Texto_Livros, Padroes_Palavras[indexRealPattern], resultKnuth);
            printResultVector(resultKnuth);

            delete[] resultBrute;
            delete[] resultKnuth;
        }

        if (instancesOp == 3){
            std::cout << "Please, enter the size of the text" << std::endl;
            std::cin >> textSize;
            std::cout << "Please, enter the size of the pattern" << std::endl;
            std::cin >> patternSize;

            char       *text = new char[textSize + 1];
            char    *pattern = new char[patternSize + 1];
            int *resultBrute = new int[textSize];
            int *resultKnuth = new int[textSize];

            generateVectorA(text, textSize, 0);
            generateVectorA(pattern, patternSize, 1);

            printCharVector(text);
            printCharVector(pattern);

            bruteForceAlgorithm(text, pattern, resultBrute);
            printResultVector(resultBrute);

            knuthMorrisPratt(text, pattern, resultKnuth);
            printResultVector(resultKnuth);

            eqResultVectors = checkEquality(resultBrute, resultKnuth);

            if(!eqResultVectors){
                std::cout << "The result vectors aren't equal" << std::endl;
            }
            else{
                std::cout << "The result vectors are equal" << std::endl;
            }

            delete[] text;
            delete[] pattern;
            delete[] resultBrute;
            delete[] resultKnuth;

        }

        if (instancesOp == 4){
            std::cout << "Please, enter the size of the text" << std::endl;
            std::cin >> textSize;
            std::cout << "Please, enter the size of the pattern" << std::endl;
            std::cin >> patternSize;

            // Adding the extra char for the \0
            textSize++;
            patternSize++;

            char       *text = new char[textSize];
            char    *pattern = new char[patternSize];
            int *resultBrute = new int[textSize];
            int *resultKnuth = new int[textSize];

            generateVectorA(text, textSize, 0);
            generateVectorA(pattern, patternSize, 0);

            printCharVector(text);
            printCharVector(pattern);

            bruteForceAlgorithm(text, pattern, resultBrute);
            printResultVector(resultBrute);

            knuthMorrisPratt(text, pattern, resultKnuth);
            printResultVector(resultKnuth);

            eqResultVectors = checkEquality(resultBrute, resultKnuth);

            if(!eqResultVectors){
                std::cout << "The result vectors aren't equal" << std::endl;
            }
            else{
                std::cout << "The result vectors are equal" << std::endl;
            }

            delete[] text;
            delete[] pattern;
            delete[] resultBrute;
            delete[] resultKnuth;
        }
        std::cout << "Do you want to continue?\n >>> Press 1 to continue\n >>> Press anything to exit." << std::endl;
        std::cin >> op;

    }
    return 0;
}