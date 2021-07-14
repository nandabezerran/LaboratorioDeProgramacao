#include <stdio.h>
#include <iostream>
#include "Heap.h"

Heap::Heap(int pHeapSize){
    heapSize = 0;
    heap = (heapNode**)malloc(sizeof(heapNode *) * heapSize);
}



void Heap::buildHeap(heapNode** pVector){
    for(int index = (heapSize-1) / 2; index >=0; index--){
        heapify(pVector, index);
    }
    heap = pVector;
}

void Heap::heapify(heapNode** &pVector, int pIndex){
    int left = getLeft(pIndex);
    int right = getRight(pIndex);
    int largest;

    if(left < heapSize && pVector[left]->quantity < pVector[pIndex]->quantity)
        largest = left;

    else
        largest = pIndex;


    if(right < heapSize && pVector[right]->quantity < pVector[largest]->quantity)
        largest = right;

    if(largest != pIndex){
        swap(pVector, pIndex, largest);
        heapify(pVector, largest);
    }
}

int Heap::getParent(int pIndex){
    if(pIndex==0){
        return 0;
    }
    return (pIndex) / 2;
}

int Heap::getLeft(int pIndex){
    return 2 * pIndex;
}

int Heap::getRight(int pIndex){
    return 2*pIndex + 1;
}

void Heap::swap(heapNode** &pVector, int pIndex, int largest){
    heapNode* aux = pVector[pIndex];
    pVector[pIndex] = pVector[largest];
    pVector[largest] = aux;
}

void Heap::insert(heapNode* pNode){
    heapSize += 1;
    int k = heapSize-1;
    while(k && pNode->quantity < heap[getParent(k-1)]->quantity){
        heap[k] = heap[getParent(k-1)];
        k = getParent(k-1);
    }
    heap[k] = pNode;
}

heapNode* Heap::minimum(){
    return heap[0];
}

heapNode* Heap::extractMinimum(){
    if (heapSize < 1){
        cout << "Heap underflow";
        return 0;
    }
    heapNode* aux = heap[0];

    heap[0] = heap[heapSize-1];
    heapSize = heapSize -1;
    heapify(heap, 0);
    return aux;
}