#include <iostream>
#include "Heap.h"
#include <fstream>
#include <sstream>
#include <time.h>
#include <chrono>

#define NULL_CHAR '#' //Define a char to represent a null node
#define SUM_NODES '$' //Define a char to represent the node which is a sum of two other nodes
#define SPECIAL_CHAR '@'
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
Heap buildHeap(dict *pDict){
    int heapSize = pDict->size();
    auto aux = (heapNode**)malloc(sizeof(heapNode *) * heapSize);
    Heap heap = Heap(heapSize);
    int i = 0;

    for (par element: (*pDict)) {
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
void countChar(dict &pDict, char &pLetter){
    if (pDict[pLetter])
        pDict[pLetter] += 1;
    else
        pDict[pLetter] = 1;
}

/* It read the file and calls the functions to count every ocurrence of
 * every letter in the file
 * @param pFileName the name of the file we want to read
 * @return a dict with all the letters and its ocurrencies
 */
dict *readFile(const string pFileName){
    ifstream inputFile(pFileName, std::ios::binary);
    dict *dictFile = new dict();

    if (!inputFile){
        cout << "Failed to open file\n";
        return nullptr;
    }

    char currReadByte;

    while (inputFile >> noskipws >> currReadByte) {
        if(inputFile.eof()){
            break;
        }
        countChar((*dictFile), currReadByte);
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
    cout << "  counting the elements..." << endl;
    dict *elements = readFile(pFileName);

    cout << "  generating the tree..." << endl;

    Heap heap = buildHeap(elements);
    heapNode *left;
    heapNode *right;
    heapNode *sumOfNodes;
    while (heap.heapSize != 0){
        if(heap.heapSize == 1){
            break;
        }
        left = heap.extractMinimum();
        right = heap.extractMinimum();
        sumOfNodes = newNode(SUM_NODES, left->quantity+right->quantity);
        sumOfNodes->right=right;
        sumOfNodes->left=left;
        heap.insert(sumOfNodes);

    }

    if(heap.heapSize == 0){
        heapNode* null = newNode(NULL,NULL);
        return null;
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
    if(pElement == nullptr){
        return pCodes;
    }
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
void writeBinaryTree(heapNode *p, vector<char> &out) {
    if (!p) {
        out.push_back(NULL_CHAR);
    } else {
        if(p->left == nullptr && p->right == nullptr) {
            if (p->letter == NULL_CHAR || p->letter == SUM_NODES || p->letter == SPECIAL_CHAR) {
                out.push_back(SPECIAL_CHAR);
            }
            out.push_back(p->letter);
        }
        else {
            out.push_back(p->letter);
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
void encodingFile(string pOriginalFile, ofstream &out, dictChar pDictCode){
    ifstream inputFile(pOriginalFile, std::ios::binary);
    char currReadByte;

    if (!inputFile){
        cout << "Failed to open file\n";
        return;
    }

    char extraBits = 0;

    // Records the position where we record the amount of extra bits at the end of the file
    streamoff extraBitsAddress = out.tellp();

    // Leaves an empty byte to record the amount of extra bits at the end of the file
    out.write(&extraBits, sizeof(char));

    int bytesPos = 0;
    int currBitPos = 0;
    char currWritingByte = 0; // It starts 0000 0000

    while (inputFile >> noskipws >> currReadByte) {
        string &bits = pDictCode[currReadByte];

        int recordedBits = 0;

        while(recordedBits < bits.size()) {
            currWritingByte = currWritingByte << 1;
            if(bits[recordedBits] == '1') {
                currWritingByte = currWritingByte | (char) 1;
            }
            recordedBits++;
            currBitPos++;
            if(currBitPos == BYTE) {
                out.write(&currWritingByte, sizeof(char));
                currWritingByte = 0;
                currBitPos = 0;
                bytesPos++;
            }
        }
    }
    if(currBitPos != 0) {

        // Adjust the last byte to have the extra bits
        extraBits = (char)(BYTE - currBitPos);
        currWritingByte = currWritingByte << extraBits;

        cout << "Extra bits on the compressed file = " << (int)extraBits << endl;

        // Write the last byte;
        //out.write(&currWritingByte, sizeof(char));

        // Write the correct amount of extra bits in the file
        out.seekp(extraBitsAddress);
        out.write(&extraBits, sizeof(char));
    }


    inputFile.close();
}

/* It generates the compressed file
 * @param pFileName the name of the file we want to compress
 * @param pExitFile the name of the file that will store de compressed file
 */
void compressFile(string pFileName, string pExitFile){
    cout << "creating huffman tree..." << endl;
    heapNode* minimunHuffman = buildHuffmanTree(pFileName);
    string code;
    dictChar dictCode;
    cout << "generating dictionary of codes..." << endl;
    dictCode = generateCodes(minimunHuffman, code, dictCode);

    ofstream myfile;
    vector<char> buffer;
    myfile.open(pExitFile, std::ios::binary);


    cout << "writing the binary tree in the file..." << endl;
    writeBinaryTree(minimunHuffman, buffer);
    // The size of the string containing our tree structure, to know exactly how much we need to read
    // from the file to get all the string, and then we save in the beginning of the file;
    int size = buffer.size();
    myfile.write((char *)&size, sizeof(int));
    // When we save the size of the tree its time to save the whole tree string in the file
    myfile.write(buffer.data(), size);

    cout << "writing the encoded data in the file..." << endl;
    encodingFile(pFileName, myfile, dictCode);

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
    if(token == SPECIAL_CHAR){
        pFile.read(&token, sizeof(char));
        pPos++;
        p = newNode(token, 0);
        pPos++;
    }
    else {
        p = newNode(token, 0);
        pPos++;
        if(token == SUM_NODES){
            readBinaryTree(p->left, pFile, pTreeStringSize, pPos);
            readBinaryTree(p->right, pFile, pTreeStringSize, pPos);
        }
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
    char extraBits = 0;
    inputFile.read(&extraBits, sizeof(char));

    cout << "Amount of extra bits read from the file = " << (int) extraBits << endl;

    ofstream myFile;
    myFile.open(fileOname, std::ios::binary);
    char currByte;
    heapNode* actualNode = root;

    char currBitPos = 0;
    inputFile.read(&currByte, sizeof(char));


    // When is end of file and the currBitPos is different of BYTE we do not read all the byte, we read only
    // BYTE - extraBits.
    while(!inputFile.eof() || currBitPos != BYTE) {
        if(inputFile.eof() && currBitPos == 0){
            break;
        }
        if(currBitPos == (char)BYTE) {
            currBitPos = 0;
            inputFile.read(&currByte, sizeof(char));
        }

        // (currByte >> ((BYTE - 1) - currBitPos) puts the actual bit we want to read in the first
        // position of the right side, then it uses binary AND to mask only this bit and whatever is
        // left is always gonna be 1 or 0
        if((currByte >> ((BYTE - 1) - currBitPos)) & (char)1){
            actualNode = actualNode->right;
        }
        else {
            actualNode = actualNode->left;
        }

        if (actualNode->left == nullptr and actualNode->right == nullptr){
            // Ignore the extra bits at the end of the file
            if(inputFile.eof() && currBitPos >= (BYTE - extraBits)) {
                cout << "reached EOF" << endl;
                break;
            }
            else {
                myFile.write(&actualNode->letter, sizeof(char));
            }
            actualNode = root;
        }

        currBitPos++;
    }
    inputFile.close();
    myFile.close();
}

int main() {
    int op = 0;
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

    }
    else {
        cout << "Invalid Operation" << endl;
    }


    return 0;
}