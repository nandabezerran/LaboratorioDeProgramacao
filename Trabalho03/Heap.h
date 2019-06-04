#ifndef TRABALHO03_HEAP_H
#define TRABALHO03_HEAP_H

#include <stdio.h>
#include <map>
#include <vector>

using namespace std;
typedef pair<char, int> par;
typedef map<char, int> dict;

struct huffmanElement{
    char letter;
    int quantity;
};

class Heap {
public:

    int heapSize;
    vector<huffmanElement> heap;

    void buildHeap(vector<huffmanElement> pVector, int pSize);
    void heapify(vector<huffmanElement> pVector, int pIndex);

    int getParent(int pIndex);

    int getLeft(int pIndex);

    int getRight(int pIndex);

    void insert(huffmanElement element);

    int minimum();

    int extractMinimum();

    void Swap(vector<huffmanElement> pVector, int pIndex, int largest);
};

#endif