#include "hash.h"

unsigned long hashFunction(char* key, unsigned long M)
{
    int i, h = key[0];
    for (i = 1; key[i] != '\0'; i++)
        h = (h * 256 + key[i]) % M;
    return h;
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
    if(temp == NULL)
        return 0;
        
    while(temp->key != key && temp->next != NULL)
        temp = temp->next;

    return temp->pair_index;
}