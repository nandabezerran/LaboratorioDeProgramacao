#include <iostream>
#include "Heap.h"
#include <fstream>
heapNode* newNode(char pLetter, int pQuantity){
    auto newNode = (heapNode *)malloc(sizeof(heapNode));
    newNode->letter = pLetter;
    newNode->quantity = pQuantity;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Heap buildHeap(dict pDict){
    int heapSize = pDict.size();
    auto aux = (heapNode**)malloc(sizeof(heapNode *) * heapSize);
    Heap heap = Heap(heapSize);
    int i = 0;

    for (par element: pDict) {
        aux[i] = newNode(element.first, element.second);
        i++;
    }

    heap.heapSize = heapSize;
    heap.buildHeap(aux);

    return heap;

}

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
    if (!inputFile){
        cout << "Failed to open file\n";
        return dictFile;
    }

    while (std::getline(inputFile, fileLine))
        dictFile = countChar(dictFile, fileLine);

    return dictFile;
}

heapNode* buildHuffmanTree(string pFileName){
    dict elements = readFile(pFileName);
    Heap heap = buildHeap(elements);
    heapNode *left;
    heapNode *right;
    heapNode *sumOfNodes;
    while (heap.heapSize != 1){
        left = heap.extractMinimum();
        right = heap.extractMinimum();
        sumOfNodes = newNode('$', left->quantity+right->quantity);
        sumOfNodes->right=right;
        sumOfNodes->left=left;
        heap.insert(sumOfNodes);

    }

    return heap.extractMinimum();

}

dictChar generateCodes(heapNode* element , string code, dictChar codes){
    if (!element->left && !element->right) {
        codes[element->letter] = code;
    }

    else{
        codes = generateCodes(element->left, code+ "0", codes);
        codes = generateCodes(element->right, code+ "1", codes);
    }

    return codes;
}


int main() {
    string fileName = "Test.txt";
    heapNode* minimunHuffman = buildHuffmanTree(fileName);
    string code;
    dictChar dictCode;

    dictCode = generateCodes(minimunHuffman, code, dictCode);
    for (parChar element: dictCode){
        cout << element.first << ":" << element.second<< endl;
    }

    return 0;
}