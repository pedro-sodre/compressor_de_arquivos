#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

typedef struct HuffmanNode{
    char data;

    int freq;

    struct HuffmanNode* left;
    struct HuffmanNode* right;

} HuffmanNode;

typedef struct HuffmanVector{
    int size;

    int maxcapacity;

    HuffmanNode** array;
} HuffmanVector;

HuffmanVector* create_empty_HuffmanVector(int maxcapacity);

HuffmanNode* createNode(char data, int freq);

void swap (HuffmanVector* Vector, int a, int b);

void MinHeapify(HuffmanVector* Vector, int i);

HuffmanNode* extractMinNode(HuffmanVector* Vector);

void insertNode(HuffmanVector* Vector, HuffmanNode* Node);

void BuildMinHeap(HuffmanVector* Vector);

void printArr(int arr[], int n);

int isLeaf(HuffmanNode* Node);

HuffmanVector* buildVector(char data[], int freq[], int size);

HuffmanNode* buildTree(char data[], int freq[], int size);

void printCodes(HuffmanNode* root, int arr[], int top);

void HuffmanCodes(char data[], int freq[], int size);
