#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Tabela hash com hashing de multiplicação e tratamento de colisões
 * por encadeamento
 *
 */
typedef struct hash_node
{
    int key;
    char value;
    struct hash_node* next;
} HashNode;

typedef struct hash 
{
    int n_entries;
    int n_keys;
    HashNode **nodes;
} Hash;

int hashFunction(int M, int key);

Hash* createHash(int entries);

void insertChained(Hash* h, int key, char value);

void freeHash(Hash* h);

char getValue(Hash* h, int key);