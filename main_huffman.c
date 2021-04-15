#include "huffman.h"
#include "hash.h"

int main(){
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

    return 0;
}
