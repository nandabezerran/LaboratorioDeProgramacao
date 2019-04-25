#include <iostream>
#include <string.h>

/* Print to the user the result vector
 * @param vector the vector we want to print
 */
void printResultVector(const int *vector){
    while(*vector != -1){
        std::cout << *vector << " ";
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

/* Calculates the vector pPiVector, where pPiVector[j] is the length of the longest proper prefix of the pattern
 * pPattern[0 ... j] which is also a suffix of this pattern.
 * @param pPattern the pattern you want to search the ocurrencies in the text
 * @param pPiVector the vector to be filled with the size of the longest prefix in every pPattern[0 ... j]
 */
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
    printResultVector(result);

    knuthMorrisPratt(text,pattern,result);
    printResultVector(result);

    return 0;
}