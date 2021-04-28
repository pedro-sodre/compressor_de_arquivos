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

    printf("Comprimindo...\n");
    CompressFile("entrada.txt", "comprimido");
    printf("Comprimido com sucesso!\n");
    printf("*********************************************************\n");
    printf("Descomprimindo...\n");
    DecompressFile("comprimido", "descomprimido.txt");
    printf("Descomprimido com sucesso!\n");


    printf("\n*********************************************************\n\n");

    Hash* H = createHash(1213);
    insertChained(H, "A", 1);
    insertChained(H, "B", 2);
    insertChained(H, "AB", 3);

    printf("AB: %lu\n", getValue(H, "AB"));
    printf("B: %lu\n", getValue(H, "B"));
    printf("A: %lu\n", getValue(H, "A"));
    printf("C: %lu\n", getValue(H, "C"));

    return 0;
}
