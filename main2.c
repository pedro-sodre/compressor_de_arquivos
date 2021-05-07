#include <time.h>
#include "huffman.h"

int main(){
  clock_t t;
  printf("\n*********************************************************\n\n");
  printf("Comprimindo Teste 2 com Huffman...\n");
  t = clock();
  CompressFile("teste2.png", "comprimido-teste2");
  t = clock() - t;
  printf("Comprimido com sucesso!\n");
  printf("Tempo de compressão: %.2f segundos\n", ((double)t)/(CLOCKS_PER_SEC));
  printf("---------------------------------------------------------\n");
  printf("Descomprimindo Teste 2 com Huffman...\n");
  t = clock();
  DecompressFile("comprimido-teste2", "descomprimido-teste2.png");
  t = clock() - t;
  printf("Descomprimido com sucesso!\n");
  printf("Tempo de descompressão: %.2f segundos\n", ((double)t)/(CLOCKS_PER_SEC));
  printf("\n*********************************************************\n\n");

    return 0;
}
