#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>


#define MAX_PREFIX_LENGHT 16
#define MAX_DICT_SIZE 1024

/**
 * Tabela hash com hashing de strings e tratamento de colisões
 * por encadeamento
 *
 */
typedef struct hash_node
{
    char key[MAX_PREFIX_LENGHT];
    __uint64_t pair_index;
    struct hash_node* next;
} HashNode;

typedef struct hash
{
    unsigned long M;
    unsigned long N;
    HashNode **nodes;
} Hash;

unsigned long hashFunction(char* key, unsigned long M);

Hash* createHash(unsigned long M);

void insertChained(Hash* H, char* key, __uint64_t index);

void freeHash(Hash* H);

__uint64_t getValue(Hash* H, char* key);

void CompressFileLZ78(const char* input, const char* output);

void DecompressFileLZ78(const char* input, const char* output);
