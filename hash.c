#include "hash.h"

#define MAX_PREFIX_LENGHT 256
#define MAX_DICT_SIZE 1024

unsigned long hashFunction(char* key, unsigned long M)
{
    int i;
    unsigned long int h = key[0];
    for (i = 1; key[i] != '\0'; i++)
        h = (h * 256 + key[i]) % M;

    return h % M;
}

Hash* createHash(unsigned long M)
{
    Hash *h = (Hash*)malloc(sizeof(Hash));

    h->M = M;
    h->N = 0;
    h->nodes = (HashNode **)malloc(M*sizeof(HashNode*));

    for(int i = 0; i < h->M; i++)
        h->nodes[i] = NULL;

    return h;
}

void insertChained(Hash* H, char* key, __uint64_t value)
{
    unsigned long index = hashFunction(key, H->M);

    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    strcpy(node->key, key);
    node->pair_index = value;

    node->next = H->nodes[index];
    H->nodes[index] = node;
    H->N++;
}

void freeHash(Hash* H)
{
    for(int i = 0; i < H->M; i++)
        free(H->nodes[i]);

    free(H);
}

__uint64_t getValue(Hash* H, char* key)
{
    unsigned long index = hashFunction(key, H->M);

    HashNode* temp = H->nodes[index];
    // printf("%lu\n", index);
    if(temp == NULL)
        return 0;

    while(temp->key != key && temp != NULL && temp->next != NULL)
    {
        //printf("%s\n", temp->key);
        temp = temp->next;
    }

    return temp->pair_index;
}

void CompressFileLZ78(const char* input, const char* output)
{
    //Abre os arquivos de input e output
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

    //Inicializa prefix com uma string vazia
    unsigned char prefix[MAX_PREFIX_LENGHT];
    strcpy(prefix, "");

    unsigned char data;

    //Índice da dupla do LZ78
    __uint64_t current_index = 1;
    
    //Último índice encontrado no dicionário
    __uint64_t last_index = 0;

    Hash* dict = createHash(MAX_DICT_SIZE);

    //Reserva espaço pro número de entradas do dicionário
    fseek(compressed, sizeof(__uint64_t), SEEK_CUR);

    while(fread(&data, 1, 1, original) > 0)
    {
        //Se o prefixo estiver cheio, zere ele
        if(strlen(prefix) >= 255)
            strcpy(prefix, "");

        strcat(prefix, &data);
        __uint64_t search_index = getValue(dict, prefix);

        //Se não encontrar o prefixo no dicionário, insira ele
        if(search_index == 0)
        {
            insertChained(dict, prefix, current_index++);

            //Escreve o índice do último prefixo existente no dicionário 
            //e o caractere significativo no arquivo de saída
            fwrite(&last_index, sizeof(__uint64_t), 1, compressed);
            fwrite(&data, sizeof(unsigned char), 1, compressed);
            
            last_index = 0;
            strcpy(prefix, "");
        }
        else
            last_index = search_index;
    }

    //Escreve o número de índices do dicionário
    fseek(compressed, 0L, SEEK_SET);
    fwrite(&dict->N, sizeof(__uint64_t), 1, compressed);

    fseek(original, 0L, SEEK_END);
    double originalSize = ftell(original);

    fseek(compressed, 0L, SEEK_END);
    double compressedSize = ftell(compressed);

    printf("Taxa de compressao: %d%%\n", (int)((100 * compressedSize) / originalSize));
}