#include "huffman.h"
#include "hash.h"
#include "trie.h"

int main(){
    //menu

    int escolha;
    const char* arquivo;
    char* arquivo_saida;
    arquivo = (const char*)malloc(sizeof(const char));
    arquivo_saida = (char*)malloc(sizeof(const char));
    int i;

    do {
        printf("\nO que você deseja fazer?");
        printf("\n1 - Comprimir Arquivo");
        printf("\n2 - Descomprimir Arquivo");
        printf("\n3 - Sair\n");

        scanf("%d", &escolha);

        switch (escolha) {
        case 1:
            printf("Qual o nome do arquivo que deseja comprimir ? (Nome do arquivo + formato) Ex: lorem_ipsum.txt\n");
            scanf("%s", arquivo);
            strcpy(arquivo_saida, arquivo);
            /*
            arquivo_saida = strtok(arquivo_saida, ".");
            printf("%s \n", arquivo);
            printf("%s \n", arquivo_saida);
            */
            //Manipula a string pra tirar o tipo do arquivo (ex: tira o .txt)
            for (i = strlen(arquivo_saida)-1; i>=0; i--){
                if (arquivo_saida[i] == '.'){
                    arquivo_saida[i] = '\0';
                    break;
                }

            }
            arquivo_saida = strcat(arquivo_saida, "-comprimido");

            printf("Deseja comprimir por 1 - Huffman ou por 2 - LZ78 ?\n");
            scanf("%d", &escolha);
            if (escolha == 1){
                printf("\nComprimindo Huffman...\n");
                CompressFile(arquivo, arquivo_saida);
                printf("'%s' Comprimido com sucesso para '%s'!\n", arquivo, arquivo_saida);
            }else if (escolha == 2){
                printf("\nComprimindo LZ78...\n");
                CompressFileLZ78Trie(arquivo, arquivo_saida);
                printf(" '%s' Comprimido com sucesso para %s!\n", arquivo, arquivo_saida);
            }
            break;
        case 2:
            printf("Qual o nome do arquivo que deseja descomprimir ? Ex: lorem_ipsum-comprimido\n");
            scanf("%s", arquivo);
            strcpy(arquivo_saida, arquivo);

            for (i = strlen(arquivo_saida)-1; i>=0; i--){
                if (arquivo_saida[i] == '.'){
                    arquivo_saida[i] = '\0';
                    break;
                }
            }
            arquivo_saida = strcat(arquivo_saida, "-descomprimido");

            printf("Deseja descomprimir por 1 - Huffman ou por 2 - LZ78 ?\n");
            scanf("%d", &escolha);
            if (escolha == 1){
                printf("\nDescomprimindo Huffman...\n");
                DecompressFile(arquivo, arquivo_saida);
                printf("'%s' Descomprimido com sucesso para '%s' !\n", arquivo, arquivo_saida);
            }else if (escolha == 2){
                printf("\nDescomprimindo LZ78...\n");
                DecompressFileLZ78Trie(arquivo, arquivo_saida);
                printf("'%s' Descomprimido com sucesso para '%s'!\n", arquivo, arquivo_saida);
            }
            break;
        case 3:
            printf("Saindo");
            break;
        default:
            printf("Erro! Insira algo válido\n");
            }
    }while(escolha != 3);

    return 0;



    // LZ78Trie* trie = createLZ78Trie();
    // insertTrie(trie, "abaabacba", 1);

    // return 0;

    printf("Comprimindo LZ78...\n");
    CompressFileLZ78Trie("lorem_ipsum.txt", "comprimidoLZ78");
    printf("Comprimido com sucesso!\n");
    printf("*********************************************************\n");
    printf("Descomprimindo LZ78...\n");
    DecompressFileLZ78Trie("comprimidoLZ78", "descomprimidoLZ78.txt");
    printf("Descomprimido com sucesso!\n");

    // printf("\n*********************************************************\n\n");

    // printf("Comprimindo duplo...\n");
    // CompressFile("comprimidoLZ78", "comprimidoDuplo");
    // printf("Comprimido com sucesso!\n");
    // printf("*********************************************************\n");
    // printf("Descomprimindo duplo...\n");
    // DecompressFile("comprimidoDuplo", "descomprimidoDuploHuffman");
    // DecompressFileLZ78Trie("descomprimidoDuploHuffman", "descomprimidoDuplo.txt");
    // printf("Descomprimido com sucesso!\n");

    printf("\n*********************************************************\n\n");

    printf("Comprimindo Huffman...\n");
    CompressFile("lorem_ipsum.txt", "comprimidoHuffman");
    printf("Comprimido com sucesso!\n");
    printf("*********************************************************\n");
    printf("Descomprimindo Huffman...\n");
    DecompressFile("comprimidoHuffman", "descomprimidoHuffman.txt");
    printf("Descomprimido com sucesso!\n");

    // printf("\n*********************************************************\n\n");

    // printf("Comprimindo duplo2...\n");
    // CompressFileLZ78Trie("comprimidoHuffman", "comprimidoDuplo2");
    // printf("Comprimido com sucesso!\n");
    // printf("*********************************************************\n");
    // printf("Descomprimindo duplo2...\n");
    // DecompressFileLZ78Trie("comprimidoDuplo2", "descomprimidoDuplo2LZ78");
    // DecompressFile("descomprimidoDuplo2LZ78", "descomprimidoDuplo2.txt");
    // printf("Descomprimido com sucesso!\n");

    printf("\n*********************************************************\n\n");

    // printf("Comprimindo imagem LZ78...\n");
    // CompressFileLZ78Trie("Trie.png", "comprimidoimagemLZ782");
    // printf("Comprimido com sucesso!\n");
    // printf("*********************************************************\n");
    // printf("Descomprimindo LZ78...\n");
    // DecompressFileLZ78Trie("comprimidoimagemLZ782", "descomprimidoimagemLZ782.png");
    // printf("Descomprimido com sucesso!\n");

    return 0;
}
