#include <time.h>
#include "huffman.h"
#include "hash.h"
#include "trie.h"

int main(){
  clock_t t;
  printf("\n*********************************************************\n\n");

  printf("Comprimindo Teste 1 com LZ78Trie...\n");
  t = clock();
  CompressFileLZ78Trie("teste1.txt", "comprimidoLz-teste1");
  t = clock() - t;
  printf("Comprimido com sucesso!\n");
  printf("Tempo de compressão: %.2f segundos\n", ((double)t)/(CLOCKS_PER_SEC));
  printf("---------------------------------------------------------\n");
  printf("Descomprimindo Teste 1 com LZ78Trie...\n");
  t = clock();
  DecompressFileLZ78Trie("comprimidoLz-teste1", "descomprimidoLZ-teste1.txt");
  t = clock()- t;
  printf("Descomprimido com sucesso!\n");
  printf("Tempo de descompressão: %.2f segundos\n", ((double)t)/(CLOCKS_PER_SEC));
  printf("\n*********************************************************\n\n");

  printf("Comprimindo Teste 1 com Huffman...\n");
  t = clock();
  CompressFile("teste1.txt", "comprimidoHuf-teste1");
  t = clock() - t;
  printf("Comprimido com sucesso!\n");
  printf("Tempo de compressão: %.2f segundos\n", ((double)t)/(CLOCKS_PER_SEC));
  printf("---------------------------------------------------------\n");
  printf("Descomprimindo Teste 1 com Huffman...\n");
  t = clock();
  DecompressFile("comprimidoHuf-teste1", "descomprimidoHuf-teste1.txt");
  t = clock() - t;
  printf("Descomprimido com sucesso!\n");
  printf("Tempo de descompressão: %.2f segundos\n", ((double)t)/(CLOCKS_PER_SEC));

  printf("\n*********************************************************\n\n");

    return 0;
}
