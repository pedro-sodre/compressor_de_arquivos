all: output clean

output: huffman.o hash.o main_huffman.o trie.o
	gcc -g -o output trie.o huffman.o hash.o main_huffman.o -lm

huffman.o: huffman.c
	gcc -g -o huffman.o -c huffman.c

main_huffman.o: main_huffman.c
	gcc -g -o main_huffman.o -c main_huffman.c

hash.o: hash.c
	gcc -g -o hash.o -c hash.c

trie.o: trie.c
	gcc -g -o trie.o -c trie.c

clean: 
	rm -f *.o

execClean:
	rm -f output