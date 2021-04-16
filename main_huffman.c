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
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };

    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmanCodes(arr, freq, size);

    int binaries[] = {1100, 1101, 100, 101, 111, 0};

    Hash* hash = createHash(6);

    for(int i = 0; i < 6; i++)
        insertChained(hash, binaries[i], arr[i]);

    printf("\n***************************************************************\n\n");

    for(int i = 0; i < 6; i++)
        printf("%d: %c\n", binaries[i], getValue(hash, binaries[i]));

    return 0;*/
}
