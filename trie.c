#include "trie.h"

LZ78Trie* createLZ78Trie()
{
    LZ78Trie* trie = (LZ78Trie*)malloc(sizeof(LZ78Trie));

    for(int i = 0; i < 256; i++)
        trie->nodes[i] = NULL;

    trie->N = 0;
    trie->pair_index = 0;
}

void insertTrie(LZ78Trie* trie, unsigned char* str, unsigned int index)
{
    if(!trie)
    {
        printf("Trie inválida!");
        exit(1);
    }

    unsigned char c = str[0];
    LZ78Trie* current_node = trie;
    unsigned int i = 1;

    while(c != '\0')
    {
        if(!current_node->nodes[c])
        {
            LZ78Trie* new_node = createLZ78Trie();
            current_node->nodes[c] = new_node;
            current_node->N++;
            trie->N++;
        }

        current_node = current_node->nodes[c];
        c = str[i++];
    }

    current_node->pair_index = index;
}

void freeTrie(LZ78Trie* trie)
{
    if(trie)
    {
        for(int i = 0; i < 256; i++)
        {
            if(trie->nodes[i])
            {
                freeTrie(trie->nodes[i]);
                trie->nodes[i] = NULL;
            }
        }
    }
    free(trie);
    trie = NULL;
}

void CompressFileLZ78Trie(const char* input, const char* output)
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

    LZ78Trie* dict = createLZ78Trie();
    LZ78Trie* current_node = dict;

    //Inicializa prefix com uma string vazia
    unsigned char prefix[MAX_TRIE_HEIGHT];
    prefix[0] = '\0';

    unsigned char data;

    //Índice da dupla do LZ78
    unsigned int current_index = 1;

    //Último índice encontrado no dicionário
    unsigned int last_index = 0;

    //Reserva espaço pro número de entradas do dicionário
    fseek(compressed, sizeof(unsigned int), SEEK_CUR);

    while(fread(&data, sizeof(unsigned char), 1, original) > 0)
    {
        //Transforma o caracter em string
        unsigned char str[2];
        str[0] = data;
        str[1] = '\0';

        strcat(prefix, str);

        if(!current_node->nodes[data] || strlen(prefix) >= MAX_TRIE_HEIGHT - 1)
        {
            insertTrie(dict, prefix, current_index++);

            //Escreve o índice do último prefixo existente no dicionário
            //e o caractere significativo no arquivo de saída
            fwrite(&last_index, sizeof(unsigned int), 1, compressed);
            fwrite(&data, sizeof(unsigned char), 1, compressed);
            last_index = 0;

            current_node = dict;

            prefix[0] = '\0';
        }
        else
        {
            last_index = current_node->nodes[data]->pair_index;
            current_node = current_node->nodes[data];
        }
    }
    if(data == '\0' && last_index != 0){
        fwrite(&last_index, sizeof(unsigned int), 1, compressed);
        fwrite(&data, sizeof(unsigned char), 1, compressed);
        current_index++;
    }
    else if(prefix[0] != '\0'){
        unsigned char empty = '\0';
        fwrite(&last_index, sizeof(unsigned int), 1, compressed);
        fwrite(&empty, sizeof(unsigned char), 1, compressed);
    }
    fseek(compressed, 0L, SEEK_SET);
    fwrite(&current_index, sizeof(unsigned int), 1, compressed);

    fseek(original, 0L, SEEK_END);
    double originalSize = ftell(original);

    fseek(compressed, 0L, SEEK_END);
    double compressedSize = ftell(compressed);

    freeTrie(dict);

    printf("Arquivo final com %d%% do tamanho do original.\n", (int)((100 * compressedSize) / originalSize));
}

void DecompressFileLZ78Trie(const char* input, const char* output){
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
    unsigned int max_index = 0;
    fread(&max_index, sizeof(unsigned int), 1, compressed);

    //Inicializa o vetor de strings
    unsigned char** string_array = (unsigned char**)malloc(max_index * sizeof(unsigned char*));
    for(unsigned int i = 0; i < max_index; i++)
    {
        string_array[i] = (unsigned char*)malloc(MAX_TRIE_HEIGHT * sizeof(unsigned char));
        string_array[i][0] = '\0';
    }

    //Inicializa a string que guardará os prefixos
    unsigned char prefix[MAX_TRIE_HEIGHT];
    strcpy(prefix, "");
    //caracter significativo lido no arquivo comprimido
    int data;
    //Índice do atual do vetor para adicionar novos prefixos
    unsigned int array_index = 0;
    //Índice que será lido no arquivo comprimido
    unsigned int current_index = 0;

    //Lê o ínidice atual presente no arquivo comprimido
    while(fread(&current_index, sizeof(unsigned int), 1, compressed) > 0){
        //Se for 0, é um caracter sozinho
        if(current_index == 0){
            fread(&data, sizeof(unsigned char), 1, compressed);
            fwrite(&data, sizeof(unsigned char), 1, decompressed);
            //Transforma o caracter em string
            unsigned char str[2];
            str[0] = data;
            str[1] = '\0';
            //Adiciona ele ao vetor de strings conhecidas
            strcpy(string_array[array_index], str);
            array_index++;
        }
        //Se não for 0, ele precisará buscar no vetor o prefixo conhecido
        else{
            fread(&data, sizeof(unsigned char), 1, compressed);
            prefix[0] = '\0';
            strcpy(prefix, string_array[current_index - 1]);
            unsigned char str[2];
            str[0] = data;
            str[1] = '\0';
            //Junta com o caracter significativo
            strcat(prefix, str);
            //Escreve no arquivo de saída a string inteira
            int i;
            unsigned char temp;
            for(i = 0 ; i < strlen(prefix); i ++){
                temp = prefix[i];
                fwrite(&temp, sizeof(unsigned char), 1, decompressed);
            }
            //Adiciona a nova string ao vetor
            strcpy(string_array[array_index], prefix);
            array_index++;
        }
    }
}
