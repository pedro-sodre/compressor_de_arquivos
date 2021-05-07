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

//Cria um HuffmanVector vazia de tamanho atual 0 e capacidade máxima "maxcapacity"
HuffmanVector* create_empty_HuffmanVector(int maxcapacity){

    HuffmanVector* temp = (HuffmanVector*)malloc(sizeof(HuffmanVector));

    temp->maxcapacity = maxcapacity;
    temp->size = 0;
    temp->array = (HuffmanNode**)malloc(temp->maxcapacity * sizeof(HuffmanNode*));
}

//Cria um HuffmanNode que armazena um char e sua frequência
HuffmanNode* createNode(unsigned char data, int freq){
    HuffmanNode* temp = (HuffmanNode*)malloc(sizeof(HuffmanNode));

    temp->left = NULL;
    temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

//Troca dois nós de lugar dentro do vetor
void swap (HuffmanVector* Vector, int a, int b) {
   HuffmanNode* temp = Vector->array[a];
   Vector->array[a] = Vector->array[b];
   Vector->array[b] = temp;
}

//Transforma uma sub-árvore em um Heap-mínimo
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

//Extrai o nó de menor frequência do vetor, como o vetor é um Heap mínimo esse elemento fica sempre na primeira posição
HuffmanNode* extractMinNode(HuffmanVector* Vector){
    HuffmanNode* temp = Vector->array[0];
    Vector->array[0] = Vector->array[Vector->size -1];
    Vector->size = Vector->size -1;
    MinHeapify(Vector, 0);
    return temp;
}

//Insere um novo nó no vetor, e faz um loop para garantir que ele continue sendo um Heap mínimo
void insertNode(HuffmanVector* Vector, HuffmanNode* Node){
    Vector->size = Vector->size + 1;
    int i = Vector->size -1;
    while(i > 0 && Node->freq < Vector->array[pai(i)]->freq){
        Vector->array[i] = Vector->array[pai(i)];
        i = pai(i);
    }
    Vector->array[i] = Node;
}

//Torna o vetor como um todo em um Heap mínimo
void BuildMinHeap(HuffmanVector* Vector){
    int i;
    for(i = (Vector->size/2) -1; i >= 0; i--){
        MinHeapify(Vector, i);
    }
}

//Verifica se o nó é uma folha
int isLeaf(HuffmanNode* Node){
    return (!(Node->left) && !(Node->right));
}

//Constrói um vetor usando como base uma lista que contém a frequência de cada char
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

//Transforma o vetor que contém os nós e é um Heap mínimo, em uma árvore binária
HuffmanNode* buildTree(unsigned int byteList[], int size){
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode* top;

    HuffmanVector* Vector = buildVector(byteList, size);

    while(Vector->size != 1){
        //Extrai os dois nós de menor frequência
        left = extractMinNode(Vector);
        right = extractMinNode(Vector);
        //Cria um nó que não representa um caracter, mas contém as frequências somadas de seus filhos
        top =createNode('@', left->freq + right->freq);
        top->left = left;
        top->right = right;
        //Insere o novo nó de volta no vetor
        insertNode(Vector, top);
    }
    //Retorna o último elemento que sobra no vetor, sendo ele a raiz de árvore binária de Huffman
    return extractMinNode(Vector);
}

//Percorre a árvore de Huffman em busca de um elemento específico e enquanto percorre a árvore vai adicionando
// o seu código a um vetor que contém 0 ou 1 nas posições, dependedo do caminho percorrido na árvore
int getCode(HuffmanNode* Node, unsigned char data, char arr[], int size){

    if(isLeaf(Node) && Node->data == data){
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

//Lê o arquivo e calcula a frequência de cada caracter
void BuildFrequencyList(FILE *entrada, unsigned int byteList[]){
    unsigned char data;
    while(fread(&data, 1, 1, entrada) > 0){
        //É possível saber qual caracter possui qual frequência, já que o índice do vetor representa o caracter es ASCII
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
    //Lista de frequência de cada caracter
    unsigned int byteList[256] = {0};
    //Constrói a lista
    BuildFrequencyList(original, byteList);
    //Constrói a árvore binária de Huffman usando a byteList como base
    HuffmanNode* root = buildTree(byteList, 256);
    //Escreve a byteList no começo do arquivo, para poder usar na descompressão depois
    fwrite(byteList, 256, sizeof(byteList[0]), compressed);
    //Deixa um espaço em branco para poder escrever o tamanho do arquivo depois
    fseek(compressed, sizeof(int), SEEK_CUR);

    unsigned char data;
    int size = 0;
    unsigned char aux = 0;
    //Lê o arquivo inteiro novamente, caracter por caracter, escrevendo o arquivo de saída
    while(fread(&data, 1, 1, original) > 0){
        char arr[1024] = {0};
        //Pega o código do caracter sendo lido atualmente
        getCode(root, data, arr, 0);
        int i;
        //Percorre o array que contém o código
        for(i = 0; arr[i] != '\0'; i++){
            //Como o aux já um byte cheio de 0, só é necessário colocar os 1 nos lugares certos
            if(arr[i] == '1'){
                aux = aux | (1 << (size % 8));
            }
            size++;
            //Quando fecha 8 bits, ele escreve na saída, já que só pode escrever no mínimo 1 byte
            if(size % 8 == 0){
                fwrite(&aux, 1, 1, compressed);
                //Quando escreve o byte o aux volta a ser vários 0
                aux = 0;
            }
            //Se o código no caracter não fecha 8 bits, o valor de aux é mantido para ser juntado ao próximo caracter
        }
    }
    //Escreve os bits que sobraram no fim (se não fecharam 8 bits)
    fwrite(&aux, 1, 1, compressed);
    //Coloca o cursor do arquivo na posição onde será escrito o tamanho
    fseek(compressed, 256*sizeof(unsigned int), SEEK_SET);
    //Escreve o tamanho do arquivo
    fwrite(&size, 4, 1, compressed);

    //Procura e escreve os tamanhos dos arquivos de entrada e saída para comparação posterior
    fseek(original, 0L, SEEK_END);
    double originalSize = ftell(original);

    fseek(compressed, 0L, SEEK_END);
    double compressedSize = ftell(compressed);

    printf("Arquivo final com %d%% do tamanho do original.\n", (int)((100 * compressedSize) / originalSize));
}

void DecompressFile(const char *input, const char *output)
{
    //Abre os arquivos de entrada (comprimido - compressed) e saída (descomprimido - decompressed)
    FILE *compressed = fopen(input, "rb");
    if(!compressed){
        printf("Error opening input file");
        exit(0);
    }

    FILE *decompressed = fopen(output, "wb");
    if(!decompressed){
        printf("Error opening output file");
        exit(0);
    }

    unsigned int byteList[256];
    int size;

    //Lê os dados da lista de bytes (frequências de cada caractere) e tamanho do arquivo comprimido
    //e armazena em variáveis locais
    fread(&byteList, sizeof(unsigned int), 256, compressed);
    fread(&size, sizeof(int), 1, compressed);

    //Constrói a árvore de Huffman com base na lista de bytes
    HuffmanNode* root = buildTree(byteList, 256);

    unsigned char data;
    HuffmanNode* aux_node = root;
    unsigned char mask = 0;

    //Lê o restante do arquivo comprimido byte por byte
    while(fread(&data, sizeof(unsigned char), 1, compressed) > 0)
    {
        mask = 1;
        while(mask > 0 && size > 0)
        {
            //Se o bit atual é 1, pega a subárvore da direita, se é 0, a da esquerda
            aux_node = (mask & data) ? aux_node->right : aux_node->left;

            mask <<= 1;
            --size;

            //Se é um nó folha, escreve o caractere contido nele no arquivo descomprimido e volta para o início da árvore
            if(!aux_node->left && !aux_node->right)
            {
                fwrite(&aux_node->data, sizeof(unsigned char), 1, decompressed);
                aux_node = root;
            }
        }
    }
}
