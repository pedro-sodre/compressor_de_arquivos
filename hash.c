#include "hash.h"

int hashFunction(int M, int key)
{
    double mult = (key*0.618033);
    return (int)M*(mult - (int)mult);
}

Hash* createHash(int entries)
{
    Hash *h = (Hash*)malloc(sizeof(Hash));

    //Pega a potência de dois mais próxima por baixo
    //do número de entradas passado para construir a hash
    //e utiliza ela no lugar (útil para hashing por multiplicação)
    int max_entries = pow(2, (int)log2(entries));

    h->n_entries = max_entries;
    h->n_keys = 0;
    h->nodes = (HashNode **)malloc(max_entries*sizeof(HashNode*));

    for(int i = 0; i < h->n_entries; i++)
        h->nodes[i] = NULL;

    return h;
}

void insertChained(Hash* h, int key, char value)
{
    int index = hashFunction(h->n_entries, key);

    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->key = key;
    node->value = value;

    node->next = h->nodes[index];
    h->nodes[index] = node;
    h->n_keys++;
}

void freeHash(Hash* h)
{
    for(int i = 0; i < h->n_entries; i++)
        free(h->nodes[i]);

    free(h);
}

char getValue(Hash* h, int key)
{
    int index = hashFunction(h->n_entries, key);

    HashNode* temp = h->nodes[index];
    if(temp == NULL)
    {
        printf("ERRO! Chave inválida!");
        exit(1);
    }

    while(temp->key != key && temp != NULL)
        temp = temp->next;

    return temp->value;
}