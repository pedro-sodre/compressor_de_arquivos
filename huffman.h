#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <limits.h>

typedef struct HuffmanNode{
    unsigned char data;

    int freq;

    struct HuffmanNode* left;
    struct HuffmanNode* right;

} HuffmanNode;

typedef struct HuffmanVector{
    int size;

    int maxcapacity;

    HuffmanNode** array;

} HuffmanVector;

int pai (int i);

int esquerda (int i);

int direita (int i);

HuffmanVector* create_empty_HuffmanVector(int maxcapacity);

HuffmanNode* createNode(unsigned char data, int freq);

void swap (HuffmanVector* Vector, int a, int b);

void MinHeapify(HuffmanVector* Vector, int i);

HuffmanNode* extractMinNode(HuffmanVector* Vector);

void heap_decrease_key (HuffmanVector* Vector, int i, HuffmanNode* Node);

void insertNode(HuffmanVector* Vector, HuffmanNode* Node);

void BuildMinHeap(HuffmanVector* Vector);

int isLeaf(HuffmanNode* Node);

HuffmanVector* buildVector(unsigned int byteList[], int size);

HuffmanNode* buildTree(unsigned int byteList[], int size);

int HuffmanCodes(HuffmanNode* Node, unsigned char data, char arr[], int size);

void getFrequency(FILE *entrada, unsigned int byteList[]);

void CompressFile(const char *input, const char *output);
