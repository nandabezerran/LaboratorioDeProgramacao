#include <iostream>
#include <map>
#include "Heap.h"
#include <fstream>
typedef map<char, int> dict;
typedef pair<char, int> par;


dict countChar(dict pDict, string pText){
    int i = 0;
    while(pText[i] != '\0'){
        if (pDict[pText[i]])
            pDict[pText[i]] += 1;
        else
            pDict[pText[i]] = 1;
        i++;
    }
    return pDict;
}

dict readFile(const string pFileName){
    ifstream inputFile(pFileName);
    dict dictFile;
    string fileLine;
    cout << pFileName << endl;
    if (!inputFile){
        cout << "Failed to open file\n";
        return dictFile;
    }

    while (std::getline(inputFile, fileLine))
        dictFile = countChar(dictFile, fileLine);

    return dictFile;
}


int main() {
    string fileName = "Test.txt";
    dict test = readFile(fileName);

    for(par element: test){
        cout << element.first << " : " << element.second << endl;
    }

    return 0;
}