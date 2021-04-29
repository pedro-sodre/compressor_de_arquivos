#include "huffman.h"
#include "hash.h"

int main(){
    //menu
    /*
    int escolha;
    do {
        printf("\nO que você deseja fazer?");
        printf("\n1 - Comprimir Arquivo");
        printf("\n2 - Descomprimir Arquivo");
        printf("\n3 - Sair\n");

        scanf("%d", &escolha);

        switch (escolha) {
        case 1:
            printf("Comprimindo");
            //comprimir();
            break;
        case 2:
            printf("Descomprimindo");
            //descomprimir();
            break;
        case 3:
            printf("Saindo");
            break;
        default:
            printf("Erro! Insira algo válido\n");
            }
    }while(escolha != 3);

    return 0;

    */

    printf("Comprimindo LZ78...\n");
    CompressFileLZ78("entrada2.txt", "comprimidoLZ78");
    printf("Comprimido com sucesso!\n");
    printf("*********************************************************\n");
    printf("Descomprimindo LZ78...\n");
    DecompressFileLZ78("comprimidoLZ78", "descomprimidoLZ78.txt");
    printf("Descomprimido com sucesso!\n");

    // printf("\n*********************************************************\n\n");   

    // printf("Comprimindo duplo...\n");
    // CompressFile("comprimidoLZ78", "comprimidoDuplo");
    // printf("Comprimido com sucesso!\n");
    // printf("*********************************************************\n");
    // printf("Descomprimindo duplo...\n");
    // DecompressFile("comprimidoDuplo", "descomprimidoDuploHuffman");
    // DecompressFileLZ78("descomprimidoDuploHuffman", "descomprimidoDuplo.txt");
    // printf("Descomprimido com sucesso!\n");

    printf("\n*********************************************************\n\n");

    printf("Comprimindo Huffman...\n");
    CompressFile("entrada2.txt", "comprimidoHuffman");
    printf("Comprimido com sucesso!\n");
    printf("*********************************************************\n");
    printf("Descomprimindo Huffman...\n");
    DecompressFile("comprimidoHuffman", "descomprimidoHuffman.txt");
    printf("Descomprimido com sucesso!\n");

    printf("\n*********************************************************\n\n");

    // printf("Comprimindo duplo2...\n");
    // CompressFileLZ78("comprimidoHuffman", "comprimidoDuplo2");
    // printf("Comprimido com sucesso!\n");
    // printf("*********************************************************\n");
    // printf("Descomprimindo duplo2...\n");
    // DecompressFileLZ78("comprimidoDuplo2", "descomprimidoDuplo2LZ78");
    // DecompressFile("descomprimidoDuplo2LZ78", "descomprimidoDuplo2.txt");
    // printf("Descomprimido com sucesso!\n");

    // printf("\n*********************************************************\n\n");

    return 0;
}
