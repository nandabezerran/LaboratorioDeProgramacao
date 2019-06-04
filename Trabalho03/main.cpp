#include <iostream>
#include "Heap.h"
#include <fstream>

vector<huffmanElement> countChar(vector<huffmanElement> pElements, string pText){
    int i = 0;
    bool found = false;
    while(pText[i] != '\0'){

        for(int j = 0; j < pElements.size(); j++){
            if(pElements[j].letter == pText[i]){
                pElements[j].quantity += 1;
                found = true;
            }
        }

        if (!found){
            huffmanElement aux = {pText[i],1};
            pElements.push_back(aux);
        }

        i++;
        found = false;
    }
    return pElements;
}

vector<huffmanElement> readFile(const string pFileName){
    ifstream inputFile(pFileName);
    vector<huffmanElement> letters;
    vector<huffmanElement> aux;
    string fileLine;
    if (!inputFile){
        cout << "Failed to open file\n";
        return letters;
    }

    while (std::getline(inputFile, fileLine)) {
        aux = countChar(letters, fileLine);
        letters.clear();
        letters = aux;
        aux.clear();
    }
    return letters;
}


int main() {
    string fileName = "Test.txt";
    vector<huffmanElement> test = readFile(fileName);
    Heap huffmanHeap;
    //huffmanHeap.buildHeap(test, test.size());
    if(test.empty()){
        cout << "empty" << endl;
    }
    for(int j = 0; j < test.size(); j++){
        cout << test[j].letter << " : " << test[j].quantity << endl;
    }

    return 0;
}