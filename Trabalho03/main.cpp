#include <iostream>
#include "Heap.h"
#include <fstream>
#include <sstream>

#define NULL_CHAR (char)219
#define SUM_NODES (char)192
#define BYTE 8
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

dict countChar(dict pDict, char pLetter){
    if (pDict[pLetter])
        pDict[pLetter] += 1;
    else
        pDict[pLetter] = 1;
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

    char letter;
    while (inputFile >> noskipws >> letter)
        dictFile = countChar(dictFile, letter);

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
        sumOfNodes = newNode(SUM_NODES, left->quantity+right->quantity);
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

void writeBinaryTree(heapNode *p, stringstream &out) {
    if (!p) {
        out << NULL_CHAR;
    } else {
        out << p->letter;
        if(p->letter == SUM_NODES) {
            writeBinaryTree(p->left, out);
            writeBinaryTree(p->right, out);
        }
    }
}

void encodingFile(string pOriginalFile, string CompressFile, stringstream &out, dictChar pDictCode){
    ifstream inputFile(pOriginalFile);
    string fileLine;
    if (!inputFile){
        cout << "Failed to open file\n";
        return;
    }
    char letter;
    while (inputFile >> noskipws >> letter) {
        for (parChar element: pDictCode) {
            if (letter == element.first) {
                out << element.second;
            }
        }
    }
}

void compressFile(string pFileName, string pExitFile){
    heapNode* minimunHuffman = buildHuffmanTree(pFileName);
    string code;
    dictChar dictCode;
    dictCode = generateCodes(minimunHuffman, code, dictCode);

    ofstream myfile;
    std::stringstream buffer;
    myfile.open(pExitFile, std::ios::binary);
    writeBinaryTree(minimunHuffman, buffer);

    int size = buffer.str().length();
    myfile.write((char *)&size, sizeof(int));
    myfile.write(buffer.str().c_str(), size);

    stringstream encondingAux;
    encodingFile(pFileName,pExitFile, encondingAux, dictCode);
    string encodedString = encondingAux.str();

    int bytesPos = 0;
    auto numBits = (long int)encodedString.length();
    int extraZeros =  BYTE - (numBits % BYTE);
    myfile.write((char *)&numBits, sizeof(long int));

    for (int j = 0; j < extraZeros; ++j) {
        encodedString += '0';
    }

    while(bytesPos + BYTE <= numBits + extraZeros) {
        char c = 0;
        for (int i = bytesPos; i < bytesPos + BYTE; ++i) {
            c = c << 1;
            if (encodedString[i] == '1') {
                c = c | (char) 1;
            }
        }
        bytesPos+= BYTE;
        myfile.write(&c, sizeof(char));
    }
    myfile.close();

}

void readBinaryTree(heapNode *&p, ifstream &pFile, int &pTreeStringSize, int &pPos) {
    if (pPos >= pTreeStringSize){
        return;
    }
    char token = 0;
    pFile.read(&token, sizeof(char));
    if (token == NULL_CHAR) {
        pPos++;
        return;
    }
    p = newNode(token, 0);
    pPos++;
    if(token == SUM_NODES) {
        readBinaryTree(p->left, pFile, pTreeStringSize, pPos);
        readBinaryTree(p->right, pFile, pTreeStringSize, pPos);
    }
}

string decodingFile(heapNode *root, string pFileName){
    string text;
    struct heapNode* actualNode = root;
    for (char letter : pFileName) {
        if (letter == '0')
            actualNode = actualNode->left;
        else
            actualNode = actualNode->right;

        if (actualNode->left== nullptr and actualNode->right== nullptr){
            text += actualNode->letter;
            actualNode = root;
        }
    }
    return text+'\0';
}

void decompressFile(string pFileName){
    ifstream inputFile(pFileName, std::ios::binary);
    string fileLine;
    if (!inputFile){
        cout << "Failed to open file\n";
        return;
    }
    heapNode* root;

    int pos = 0;
    int treeStringSize = 0;
    inputFile.read((char *)&treeStringSize, sizeof(int));
    readBinaryTree(root, inputFile, treeStringSize, pos);

    long int numBits = 0;
    inputFile.read((char*)&numBits, sizeof(long int));
    cout << numBits << endl;

    string pText;
    ofstream myfile;
    myfile.open (pFileName+"1"+".txt");
    char currByte;
    heapNode* actualNode = root;
    for (long int i = 0; i < numBits ; ++i) {
        long int currBitPos = i % BYTE;
        if(currBitPos == 0) {
            inputFile.read(&currByte, sizeof(char));
        }
        if((currByte >> ((BYTE - 1) - i)) & (char)1){
            actualNode = actualNode->right;
        }
        //1101 0110
        else
            actualNode = actualNode->left;

        if (actualNode->left== nullptr and actualNode->right== nullptr){
            myfile << actualNode->letter;
            actualNode = root;
        }

    }
    inputFile.close();
    myfile.close();
}

int main() {
    string fileName = "Test.txt";
    compressFile(fileName, "filename.huf");
    decompressFile("filename.huf");

    return 0;
}