#include <iostream>
#include "Heap.h"
#include <fstream>
#include <sstream>
#include <time.h>
#include <chrono>

#define NULL_CHAR (char)219 //Define a char to represent a null node
#define SUM_NODES (char)192 //Define a char to represent the node which is a sum of two other nodes
#define BYTE 8 //To make the code more clear, define a name to represent the size of a byte

/* It creates a new heapNode structure, already allocating the memory
 * @param pLettter the letter of the text 
 * @param pQuantity the number of occurrencies of the pLetter
 * @return heapNode* to the new node created
 */
heapNode* newNode(char pLetter, int pQuantity){
    auto newNode = (heapNode *)malloc(sizeof(heapNode));
    newNode->letter = pLetter;
    newNode->quantity = pQuantity;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

/* It builds a heap using a map<char, int> that we defined as a dict
 * @param pDict it's a map wher the key is a letter and the content is the
 *        number of occurrences
 * @return heap a object from the classe Heap
 */
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

/* Its a function that count the ocurrences of each letter in the text and
 * store in a dict
 * @param pDict map<char, int> that has all the letters and the number of 
 *        ocurrences of each one.
 * @param pLetter the letter we want to add in the dictionary.
 * @return a dict updated with the pLetter
 */
dict countChar(dict pDict, char pLetter){
    if (pDict[pLetter])
        pDict[pLetter] += 1;
    else
        pDict[pLetter] = 1;
    return pDict;
}

/* It read the file and calls the functions to count every ocurrence of 
 * every letter in the file
 * @param pFileName the name of the file we want to read
 * @return a dict with all the letters and its ocurrencies
 */
dict readFile(const string pFileName){
    ifstream inputFile(pFileName, std::ios::binary);
    dict dictFile;
    string fileLine;
    int currByte;

    if (!inputFile){
        cout << "Failed to open file\n";
        return dictFile;
    }

    inputFile.seekg( 0, ios::end );
    size_t fileSize = inputFile.tellg();
    char *bytes = new char[fileSize];
    inputFile.seekg(0, ios::beg);
    inputFile.read(bytes, fileSize);
    inputFile.close();

    for (currByte = 0; currByte < fileSize; ++currByte) {
        dictFile = countChar(dictFile, bytes[currByte]);
    }

    return dictFile;
}

/* It builds the huffman tree, reading the file and producing the dict,
 * it builds the heap and then it build the huffman tree, using the
 * huffman algorithm.
 * @param pFileName the name of the file we want to use
 * @return a heapNode* to the root of the tree
 */
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

/* It go through the tree until we reach a leaf node. For every right 
 * direction we add a 1 and for every left a 0
 * @param pElement the node of the huffman tree
 * @param pCode the string we are going to create with the code of each
 *        letter according to the directions we take to reach it
 * @param pCodes map<char, string> to be filled with the codes
 * @return a dictCHar filled with the letters and its codes
 */
dictChar generateCodes(heapNode* pElement , string pCode, dictChar pCodes){
    if (!pElement->left && !pElement->right) {
        pCodes[pElement->letter] = pCode;
    }
    else{
        pCodes = generateCodes(pElement->left, pCode+ "0", pCodes);
        pCodes = generateCodes(pElement->right, pCode+ "1", pCodes);
    }

    return pCodes;
}

/* It writes a string containing the structure of the tree
 * @param *p a heapNode which starts at the root and recursively descends on the tree
 * @param &out a stringstream which is the formed string
 */
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

/* It reads each letter of the original file and forms a streangstream with the letters replaced
 * by its code
 * @param pOriginalFile the file we want to codify
 * @param &out a stringstream that will have the text of our original file codified
 * @param pDictCode a dictChar (map<char, string>) that contains the code of each letter of the original file
 */
void encodingFile(string pOriginalFile, stringstream &out, dictChar pDictCode){
    ifstream inputFile(pOriginalFile, std::ios::binary);
    char currByte;

    if (!inputFile){
        cout << "Failed to open file\n";
        return;
    }
    while (inputFile >> noskipws >> currByte) {
        for (parChar element: pDictCode) {
            if (currByte== element.first) {
                out << element.second;
            }
        }
    }
}

/* It generates the compressed file
 * @param pFileName the name of the file we want to compress
 * @param pExitFile the name of the file that will store de compressed file
 */
void compressFile(string pFileName, string pExitFile){
    heapNode* minimunHuffman = buildHuffmanTree(pFileName);
    string code;
    dictChar dictCode;
    dictCode = generateCodes(minimunHuffman, code, dictCode);

    ofstream myfile;
    std::stringstream buffer;
    myfile.open(pExitFile, std::ios::binary);


    writeBinaryTree(minimunHuffman, buffer);
    // The size of the string containing our tree structure, to know exactly how much we need to read
    // from the file to get all the string, and then we save in the beginning of the file;
    int size = buffer.str().length(); 
    myfile.write((char *)&size, sizeof(int)); 
    // When we save the size of the tree its time to save the whole tree string in the file
    myfile.write(buffer.str().c_str(), size);


    stringstream encondingAux;
    encodingFile(pFileName, encondingAux, dictCode);
    string encodedString = encondingAux.str(); // Transforming the stringstream in a cstring

    int bytesPos = 0;
    auto numBits = (long int)encodedString.length(); // Getting the size of the file content
    myfile.write((char *)&numBits, sizeof(long int));

    // If the size of the file content isn't divisible by 8 we fill with 0's to be divisible
    int extraZeros =  BYTE - (numBits % BYTE); 
    for (int j = 0; j < extraZeros; ++j) {
        encodedString += '0';
    }

    // We go through each byte of the file
    while(bytesPos + BYTE <= numBits + extraZeros) {
        char c = 0; // It starts 0000 0000
        for (int i = bytesPos; i < bytesPos + BYTE; ++i) {
            c = c << 1; // To add the letter in the first element of the right side
            if (encodedString[i] == '1') {
                c = c | (char) 1; 
            }
        }
        bytesPos+= BYTE;
        myfile.write(&c, sizeof(char));
    }

    myfile.close();

}

/* It reads the tree from the compressed file and turn it into a tree structure
 * @param *&p a heapNode to generate its children by itself
 * @param &pFile a ifstream to go through the file
 * @param &pTreeStringSize the size of the tree string
 * @param &pPos position that we are in the tree string 
 */ 
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

/* It decompress the file, decoding the codes presents in the compressed file
 * @param pFileName the name of the file we want to decompress
 */
void decompressFile(string pFileName, string fileOname){
    ifstream inputFile(pFileName, std::ios::binary);

    if (!inputFile){
        cout << "Failed to open file\n";
        return;
    }

    // Reading the size of the tree string and the tree
    int pos = 0;
    int treeStringSize = 0;
    inputFile.read((char *)&treeStringSize, sizeof(int));
    heapNode* root;
    readBinaryTree(root, inputFile, treeStringSize, pos);

    // Reading the size of the content of the file
    long int numBits = 0;
    inputFile.read((char*)&numBits, sizeof(long int));

    ofstream myfile;
    myfile.open (fileOname);
    char currByte;
    heapNode* actualNode = root;

    for (long int i = 0; i < numBits ; ++i) {
        long int currBitPos = i % BYTE;
        if(currBitPos == 0) {
            inputFile.read(&currByte, sizeof(char));
        }

        // (currByte >> ((BYTE - 1) - currBitPos) puts the actual bit we want to read in the first
        // position of the right side, then it can be 0 or 1, it compares with 1 to check if it is
        // 0 or 1
        if((currByte >> ((BYTE - 1) - currBitPos)) & (char)1){
            actualNode = actualNode->right;
        }
        
        else
            actualNode = actualNode->left;

        if (actualNode->left == nullptr and actualNode->right== nullptr){
            myfile << actualNode->letter;
            actualNode = root;
        }

    }
    inputFile.close();
    myfile.close();
}

int main() {
    int op = 0;
    int cont = 1;

    while(cont != 0) {
        cout << "If you want to compress, press 1. If you want to decompress, press 2. " << endl;
        cin >> op;
        if (op == 1) {
            string fileName;
            cout << "Enter the name of the file: " << endl;
            cin >> fileName;

            string fileAdress = "Files/" + fileName;
            string aux = fileName;
            string compressedFile = "Compressed/" + aux.erase(aux.length() - 3, aux.length()) + "huf";

            auto start = std::chrono::high_resolution_clock::now();
            compressFile(fileAdress, compressedFile);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            cout << "Time taken to compress " + fileName + " : " << duration.count() << " microseconds\n" << endl;

        } else if (op == 2) {
            string fileName;
            string decompressedFile;
            cout << "Enter the name of the file you want to decompress: " << endl;
            cin >> fileName;

            cout << "Enter the name of the decompressed file: " << endl;
            cin >> decompressedFile;

            string fileAdress = "Compressed/" + fileName;
            string aux = fileName;
            string decompressedFile1 = "Decompressed/" + decompressedFile;

            auto start = std::chrono::high_resolution_clock::now();
            decompressFile(fileAdress, decompressedFile1);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            cout << "Time taken to decompress " + fileName + " : " << duration.count() << " microseconds\n" << endl;

        } else {
            cout << "Invalid Operation" << endl;
        }
        cout << "Do you want to continue? Press any number to continue; Press 0 to exit " << endl;
        cin >> cont;
    }

    return 0;
}