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
    cout << pFileName << endl;
    if (!inputFile){
        cout << "Failed to open file\n";
        return dictFile;
    }

    while (std::getline(inputFile, fileLine))
        dictFile = countChar(dictFile, fileLine);

    return dictFile;
}

//heapNode buildHuffmanTree(string pFileName){
//    vector<heapNode> elements = readFile(pFileName);
//    Heap heap = Heap(elements.size());
//    pHeap.buildHeap(elements);
//    heapNode left;
//    heapNode right;
//    heapNode sumOfNodes;
//    while (pHeap.heapSize != 1){
//        left = pHeap.heap[pHeap.extractMinimum()];
//        right = pHeap.heap[pHeap.extractMinimum()];
//        sumOfNodes = {'$', left.quantity+right.quantity, &left, &right};
//        pHeap.insert(sumOfNodes);
//
//    }
//
//    return pHeap.minimum();
//
//}


int main() {
    string fileName = "Test.txt";
    dict test = readFile(fileName);
    for(par element: test){
        cout << element.first << " : " << element.second << endl;
    }
    Heap heap = buildHeap(test);


    for(int i=0; i<heap.heapSize; i++ ){
        cout << heap.heap[i]->letter << ":" << heap.heap[i]->quantity << endl;
    }


    return 0;
}