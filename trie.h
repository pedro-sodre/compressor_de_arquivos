#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>

#define MAX_TRIE_HEIGHT 12

/**
 * Trie (árvore de prefixos)
 */
typedef struct lz78_trie
{
    struct lz78_trie* nodes[256];
    unsigned int N;
    unsigned int pair_index;
} LZ78Trie;

LZ78Trie* createLZ78Trie();

void insertTrie(LZ78Trie* trie, unsigned char* str, unsigned int index);

void freeTrie(LZ78Trie* trie);

void CompressFileLZ78Trie(const char* input, const char* output);

void DecompressFileLZ78Trie(const char* input, const char* output);