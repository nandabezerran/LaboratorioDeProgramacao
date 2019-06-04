#include <stdio.h>
#include <iostream>
#include "Heap.h"

void Heap::buildHeap(vector<huffmanElement> pVector, int pSize){
    heapSize = pSize;

    //TODO check if the index is correct
    for(int index = (pSize-1) / 2; index >=0; index--){
        heapify(pVector, index);
    }
    heap = pVector;
}

vector<huffmanElement> Heap::heapify(vector<huffmanElement> pVector, int pIndex){
    int left = getLeft(pIndex);
    int right = getRight(pIndex);
    int largest;

    if(left <= heapSize && pVector[left].quantity < pVector[pIndex].quantity)
        largest = left;

    else
        largest = pIndex;


    if(right <= heapSize && pVector[right].quantity < pVector[largest].quantity)
        largest = right;

    if(largest != pIndex){
        pVector = Swap(pVector, pIndex, largest);
        pVector = heapify(pVector, largest);
    }
    return pVector;
}

int Heap::getParent(int pIndex){
    return pIndex / 2;
}

int Heap::getLeft(int pIndex){
    return 2 * pIndex;
}

int Heap::getRight(int pIndex){
    return 2*pIndex + 1;
}

vector<huffmanElement> Heap::Swap(vector<huffmanElement> pVector, int pIndex, int largest){
    huffmanElement aux = pVector[pIndex];
    pVector[pIndex] = pVector[largest];
    pVector[largest] = aux;
    return pVector;
}

void Heap::insert(huffmanElement element){
    heapSize = heapSize + 1;
    int k = heapSize;
    while(k > 1 && heap[getParent(k)].quantity < element.quantity){
        heap[k] = heap[getParent(k)];
        k = getParent(k);
    }
    heap[k] = element;
}

int Heap::minimum(){
    return heap[0].quantity;
}

int Heap::extractMinimum(){
    if (heapSize < 1){
        cout << "Heap underflow";
        return 0;
    }

    int max = heap[0].quantity;
    heap[0] = heap[heapSize-1];
    heapSize = heapSize -1;
    heapify(heap, 0);
    return max;
}