#include <iostream>
using std::cin;
using std::cout;

/// It increase the size of the vector when is full;
/// \param vector = vector with the numbers of the user;
/// \param vectorSize = size of that vector;
void VectorIncreaseSize(int *vector, int vectorSize){
    int *vectorAux = new (std::nothrow) int[vectorSize*2];
    for (int i = 0; i < vectorSize ; ++i) {
        vectorAux = vector;
        vectorAux = vectorAux + 1;
        vector = vector +1;
    }
    delete [] vector;
    vector = vectorAux;
}

int main() {
    int vectorSize = 1;
    int userInput = 0;
    int *vector = new(std::nothrow) int[vectorSize];
    int countVectorFilled = 0;
    int *firstElement = vector;
    int *lastElement = vector;
    do{
        cout << "Entre seu numero: \n";
        cin >> userInput;
        if(userInput < 0) {
            vector = firstElement;
            cout << "Numeros digitados \n";
            for (vector; vector != lastElement; ++vector) {
                cout << *vector << "\n";
            }
            break;
        }
        else {
            if (countVectorFilled == vectorSize) {
                VectorIncreaseSize(vector, vectorSize);
                vectorSize = vectorSize * 2;
            }
            countVectorFilled++;
            *vector = userInput;
            vector = vector + 1;
            vectorSize++;
            lastElement = vector;
        }
    }
    while(userInput > 0);

    return 0;
}