#include "huffman.h"

int pai (int i) {
   return (i - 1)/2;
}

int esquerda (int i) {
   return (i * 2) + 1;
}

int direita (int i) {
   return (i * 2) + 2;
}

HuffmanVector* create_empty_HuffmanVector(int maxcapacity){

    HuffmanVector* temp = (HuffmanVector*)malloc(sizeof(HuffmanVector));

    temp->maxcapacity = maxcapacity;
    temp->size = 0;
    temp->array = (HuffmanNode**)malloc(temp->maxcapacity * sizeof(HuffmanNode*));
}

HuffmanNode* createNode(unsigned char data, int freq){
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
    int esq = esquerda(i);
    int dir = direita(i);
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

void heap_decrease_key (HuffmanVector* Vector, int i, HuffmanNode* Node){
    if(Node->freq > Vector->array[i]->freq){
        printf("Error: nova chave maior que valor atual");
    }
    else{
        Vector->array[i] = Node;
        while(i > 0 && Vector->array[pai(i)]->freq > Vector->array[i]->freq){
            swap(Vector, pai(i), i);
            i = pai(i);
        }
    }
}

void insertNode(HuffmanVector* Vector, HuffmanNode* Node){
    Vector->size = Vector->size + 1;
    int i = Vector->size -1;
    while(i > 0 && Node->freq < Vector->array[pai(i)]->freq){
        Vector->array[i] = Vector->array[pai(i)];
        i = pai(i);
    }
    Vector->array[i] = Node;
}

void BuildMinHeap(HuffmanVector* Vector){
    int i;
    for(i = (Vector->size/2) -1; i >= 0; i--){
        MinHeapify(Vector, i);
    }
}

int isLeaf(HuffmanNode* Node){
    return (!(Node->left) && !(Node->right));
}

HuffmanVector* buildVector(unsigned int byteList[], int size){
    HuffmanVector* Vector = create_empty_HuffmanVector(size);
    int i;

    for(i=0 ; i<size ; i++){
        Vector->array[i] = createNode(i, byteList[i]);
    }
    Vector->size = size;
    BuildMinHeap(Vector);
    return Vector;
}

HuffmanNode* buildTree(unsigned int byteList[], int size){
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode* top;

    HuffmanVector* Vector = buildVector(byteList, size);

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

int getCode(HuffmanNode* Node, unsigned char data, char arr[], int size){

    if(!Node->left && !Node->right && Node->data == data){
        arr[size] = '\0';
        return 1;
    }
    else{
        int flag = 0;
        if(Node->left){
            arr[size] = '0';
            flag = getCode(Node->left, data, arr, size + 1);
        }
        if(flag == 0 && Node->right){
            arr[size] = '1';
            flag = getCode(Node->right, data, arr, size + 1);
        }
        if(flag == 0){
            arr[size] = '\0';
        }
        return flag;
    }
}

void BuildFrequencyList(FILE *entrada, unsigned int byteList[]){
    unsigned char data;
    while(fread(&data, 1, 1, entrada) > 0){
        byteList[(int)data]++;
    }
    rewind(entrada);
}

void CompressFile(const char *input, const char *output){
    FILE *original = fopen(input, "rb");
    if(!original){
        printf("Error opening input file");
        exit(0);
    }

    FILE *compressed = fopen(output, "wb");
    if(!compressed){
        printf("Error opening output file");
        exit(0);
    }

    unsigned int byteList[256] = {0};

    BuildFrequencyList(original, byteList);

    HuffmanNode* root = buildTree(byteList, 256);

    fwrite(byteList, 256, sizeof(byteList[0]), compressed);

    fseek(compressed, sizeof(int), SEEK_CUR);

    unsigned char data;
    int size = 0;
    unsigned char aux = 0;

    while(fread(&data, 1, 1, original) > 0){
        char arr[1024] = {0};
        getCode(root, data, arr, 0);
        int i;
        for(i = 0; arr[i] != '\0'; i++){
            if(arr[i] == '1'){
                aux = aux | (1 << (size % 8));
            }
            size++;
            if(size % 8 == 0){
                fwrite(&aux, 1, 1, compressed);
                aux = 0;
            }
        }
    }

    fwrite(&aux, 1, 1, compressed);

    fseek(compressed, 256*sizeof(unsigned int), SEEK_SET);

    fwrite(&size, 1, 1, compressed);

    fseek(original, 0L, SEEK_END);
    double originalSize = ftell(original);

    fseek(compressed, 0L, SEEK_END);
    double compressedSize = ftell(compressed);

    printf("\nTaxa de compressao: %d%%\n", (int)((100 * compressedSize) / originalSize));
}
