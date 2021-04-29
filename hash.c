#include "hash.h"

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

    while(temp->next != NULL)
    {   
        if(strcmp(temp->key, key) == 0)
            return temp->pair_index;
        temp = temp->next;
    }

    return 0;
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
    prefix[0] = '\0';

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
        //Transforma o caracter em string
        unsigned char str[2];
        str[0] = data;
        str[1] = '\0';

        strcat(prefix, str);
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

            // strcpy(prefix, "");
            prefix[0] = '\0';
        }
        else
        {

            if(strlen(prefix) >= MAX_PREFIX_LENGHT - 1)
            {
                insertChained(dict, prefix, current_index++);
                // printf("%s\n***********\n", prefix);
                fwrite(&last_index, sizeof(__uint64_t), 1, compressed);
                fwrite(&data, sizeof(unsigned char), 1, compressed);
                last_index = 0;
                // strcpy(prefix, "");
                prefix[0] = '\0';
            }
            else
                last_index = search_index;
        }
    }

    insertChained(dict, prefix, current_index++);
    unsigned char empty = '\0';
    fwrite(&last_index, sizeof(unsigned char), 1, compressed);
    fwrite(&empty, sizeof(unsigned char), 1, compressed);
    // dict->N++;

    //Escreve o número de índices do dicionário
    fseek(compressed, 0L, SEEK_SET);
    fwrite(&dict->N, sizeof(__uint64_t), 1, compressed);

    fseek(original, 0L, SEEK_END);
    double originalSize = ftell(original);

    fseek(compressed, 0L, SEEK_END);
    double compressedSize = ftell(compressed);

    freeHash(dict);

    printf("Taxa de compressao: %d%%\n", (int)((100 * compressedSize) / originalSize));
}

void DecompressFileLZ78(const char* input, const char* output){
    //Abre os arquivos de input e output
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

    //Lê o indíce máximo do arquivo comprimido
    __uint64_t max_index = 0;
    fread(&max_index, sizeof(__uint64_t), 1, compressed);

    //Inicializa o vetor de strings
    unsigned char** string_array = (unsigned char**)malloc(max_index * sizeof(unsigned char*));
    for(uint64_t i = 0; i < max_index; i++)
    {
        string_array[i] = (unsigned char*)malloc(MAX_PREFIX_LENGHT * sizeof(unsigned char));
        string_array[i][0] = '\0';
    }

    //Inicializa a string que guardará os prefixos
    unsigned char prefix[MAX_PREFIX_LENGHT];
    strcpy(prefix, "");
    //caracter significativo lido no arquivo comprimido
    unsigned char data;
    //Índice do atual do vetor para adicionar novos prefixos
    __uint64_t array_index = 1;
    //Índice que será lido no arquivo comprimido
    __uint64_t current_index = 0;

    //Lê o ínidice atual presente no arquivo comprimido
    while(fread(&current_index, sizeof(__uint64_t), 1, compressed) > 0){
        //Se for 0, é um caracter sozinho
        if(current_index == 0){
            //Lê o caracter ao lado do índice
            fread(&data, sizeof(unsigned char), 1, compressed);
            //Escreve apenas esse caracter
            fwrite(&data, sizeof(unsigned char), 1, decompressed);
            //Transforma o caracter em string
            unsigned char str[2];
            str[0] = data;
            str[1] = '\0';
            //Adiciona ele ao vetor de strings conhecidas
            strcpy(string_array[array_index], str);
            //Aumenta o índice atual do vetor
            array_index++;
        }
        //Se não for 0, ele precisará buscar no vetor o prefixo conhecido
        else{
            //Lê o caracter significativo
            fread(&data, sizeof(unsigned char), 1, compressed);
            //Copia para o prefixo, a string já conhecida referente ao índice lido
            prefix[0] = '\0';
            strcpy(prefix, string_array[current_index]);
            //Transforma o caracter em string
            unsigned char str[2];
            str[0] = data;
            str[1] = '\0';
            //Junta com o caracter significativo
            strcat(prefix, str);
            //Escreve no arquivo de saída a string inteira
            fwrite(&prefix, sizeof(unsigned char), strlen(prefix), decompressed);
            //Adiciona a nova string ao vetor
            strcpy(string_array[array_index], prefix);
            //Aumenta o índice atual do vetor
            array_index++;
        }
    }

}
