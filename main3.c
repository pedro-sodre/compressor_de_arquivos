#include <time.h>
#include "huffman.h"

int main(){
  clock_t t;
  printf("\n*********************************************************\n\n");
  printf("Comprimindo Teste 3 com Huffman...\n");
  t = clock();
  CompressFile("teste3.pdf", "comprimido-teste3");
  t = clock() - t;
  printf("Comprimido com sucesso!\n");
  printf("Tempo de compressão: %.2f segundos\n", ((double)t)/((CLOCKS_PER_SEC)));
  printf("---------------------------------------------------------\n");
  printf("Descomprimindo Teste 3 com Huffman...\n");
  t = clock();
  DecompressFile("comprimido-teste3", "descomprimido-teste3.pdf");
  t = clock() - t;
  printf("Descomprimido com sucesso!\n");
  printf("Tempo de descompressão: %.2f segundos\n", ((double)t)/(CLOCKS_PER_SEC));
  printf("\n*********************************************************\n\n");

    return 0;
}
