#ifndef TRABALHO03_HEAP_H
#define TRABALHO03_HEAP_H

#include <stdio.h>
#include <map>
#include <vector>

using namespace std;
typedef map<char, int> dict;
typedef map<char, string> dictChar;
typedef pair<char, int> par;
typedef pair<char, string> parChar;


struct heapNode{
    char letter;
    int quantity;
    heapNode *left;
    heapNode *right;
};

class Heap {
public:

    int heapSize;
    heapNode** heap;

    explicit Heap(int pHeapSize);
    void buildHeap(heapNode** pVector);
    void heapify(heapNode** &pVector, int pIndex);

    int getParent(int pIndex);

    int getLeft(int pIndex);

    int getRight(int pIndex);

    void insert(heapNode* element);

    heapNode* minimum();

    heapNode* extractMinimum();

    void swap(heapNode** &pVector, int pIndex, int largest);
};

#endif