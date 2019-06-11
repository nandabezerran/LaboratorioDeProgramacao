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
void writeBinaryTree(heapNode *p, ofstream &out) {
    if (!p) {
        out << "#";
    } else {
        out << p->letter;
        writeBinaryTree(p->left, out);
        writeBinaryTree(p->right, out);
    }
}

void encodingFile(string pOriginalFile, string CompressFile, ofstream &out, dictChar pDictCode){
    ifstream inputFile(pOriginalFile);
    string fileLine;
    if (!inputFile){
        cout << "Failed to open file\n";
        return;
    }

    while (std::getline(inputFile, fileLine)) {
        for (char letter : fileLine) {
            for (parChar element: pDictCode) {
                if (letter == element.first) {
                    out << element.second;
                }
            }
        }
        out << "\n";
    }
}

void compressFile(string pFileName){
    heapNode* minimunHuffman = buildHuffmanTree(pFileName);
    string code;
    dictChar dictCode;
    dictCode = generateCodes(minimunHuffman, code, dictCode);
    ofstream myfile;
    myfile.open ("filename.huf");
    writeBinaryTree(minimunHuffman, myfile);
    myfile << "\n";
    encodingFile(pFileName,"filename.huf", myfile, dictCode);
    myfile.close();

}

void readBinaryTree(heapNode *&p, string pFileLine, int &pos) {
    if (pos >= pFileLine.size()){
        return;
    }
    char token = pFileLine[pos];
    if (token == '#') {
        pos++;
        return;
    }
    p = newNode(token, 0);
    pos++;
    readBinaryTree(p->left, pFileLine, pos);
    readBinaryTree(p->right, pFileLine, pos);
}

void decodingFile(heapNode *root, heapNode *element, string fileLine, string pText){
    if(fileLine.empty()){
        return;
    }
    while(element->left || element->right){
        if (fileLine[0] == '0'){
            fileLine.erase(fileLine.begin());
            decodingFile(root, element->left, fileLine, pText);
        }
        if (fileLine[0] == '1'){
            fileLine.erase(fileLine.begin());
            decodingFile(root, element->right, fileLine, pText);
        }
    }
    pText += element->letter;
    decodingFile(root, root, fileLine, pText);
}

void decompressFile(string pFileName){
    ifstream inputFile(pFileName);
    string fileLine;
    string pText;
    if (!inputFile){
        cout << "Failed to open file\n";
        return;
    }
    heapNode* root;
    std::getline(inputFile,fileLine);
    int pos = 0;
    readBinaryTree(root, fileLine, pos);

    while (std::getline(inputFile, fileLine)) {
        decodingFile(root, root, fileLine,pText);
        pText += "\n";
    }
    inputFile.close();
    ofstream myfile;
    myfile.open (pFileName+"1"+".txt");
    myfile << pText;
    myfile.close();
}
int main() {
    string fileName = "Test.txt";
    //compressFile(fileName);
    decompressFile("filename.huf");

    return 0;
}