#include "huffman.h"

#define MAX_TREE_HT 10

HuffmanVector* create_empty_HuffmanVector(int maxcapacity){

    HuffmanVector* temp = (HuffmanVector*)malloc(sizeof(HuffmanVector));

    temp->maxcapacity = maxcapacity;
    temp->size = 0;
    temp->array = (HuffmanNode**)malloc(temp->maxcapacity * sizeof(HuffmanNode*));
}

HuffmanNode* createNode(char data, int freq){
    HuffmanNode* temp = (HuffmanNode*)malloc(sizeof(HuffmanNode));

    temp->left = NULL;
    temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

void swap (HuffmanVector* Vector, int a, int b) {
   HuffmanNode* temp = Vector->array[a];
   Vector->array[a] = Vector->array[b];
   Vector->array[b] = temp;
}

void MinHeapify(HuffmanVector* Vector, int i) {
    int esq = 2*i + 1;
    int dir = 2*i + 2;
    int menor;

    if( esq < Vector->size && Vector->array[esq]->freq < Vector->array[i]->freq)
        menor = esq;
    else
        menor = i;

    if( dir < Vector->size && Vector->array[dir]->freq < Vector->array[menor]->freq)
        menor = dir;

    if (menor != i){
        swap(Vector, i, menor );
        MinHeapify(Vector, menor);
    }
}

HuffmanNode* extractMinNode(HuffmanVector* Vector){
    HuffmanNode* temp = Vector->array[0];
    Vector->array[0] = Vector->array[Vector->size -1];
    Vector->size = Vector->size -1;
    MinHeapify(Vector, 0);
    return temp;
}

void insertNode(HuffmanVector* Vector, HuffmanNode* Node){
    Vector->size = Vector->size + 1;
    int i = Vector->size -1;
    Vector->array[i] = Node;
    BuildMinHeap(Vector);
}

void BuildMinHeap(HuffmanVector* Vector){
    int i;
    for(i = (Vector->size/2) -1; i >= 0; i--){
        MinHeapify(Vector, i);
    }
}

void printArr(int arr[], int n){
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}

int isLeaf(HuffmanNode* Node){
    return (!(Node->left) && !(Node->right));
}

HuffmanVector* buildVector(char data[], int freq[], int size){
    HuffmanVector* Vector = create_empty_HuffmanVector(size);
    int i;

    for(i=0 ; i<size ; i++){
        Vector->array[i] = createNode(data[i], freq[i]);
    }
    Vector->size = size;
    BuildMinHeap(Vector);
    return Vector;
}

HuffmanNode* buildTree(char data[], int freq[], int size){
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode* top;

    HuffmanVector* Vector = buildVector(data, freq, size);

    while(Vector->size != 1){
        left = extractMinNode(Vector);
        right = extractMinNode(Vector);
        top =createNode('@', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertNode(Vector, top);
    }
    return extractMinNode(Vector);
}

void printCodes(HuffmanNode* root, int arr[], int top){

    if (root->left) {

        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {

        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (isLeaf(root)) {

        printf("%c: ", root->data);
        printArr(arr, top);
    }
}

void HuffmanCodes(char data[], int freq[], int size){
    HuffmanNode* root = buildTree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
}
