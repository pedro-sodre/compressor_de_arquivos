all: teste1 teste2 teste3 clean
	@echo "Primeiro teste(.txt): ./teste1"
	@echo "Segundo teste(.png): ./teste2"
	@echo "Terceiro teste(.pdf): ./teste3"

teste1: huffman.o main1.o trie.o
	gcc -g -o teste1 trie.o huffman.o main1.o -lm

teste2: huffman.o main2.o
	gcc -g -o teste2 huffman.o main2.o -lm

teste3: huffman.o main3.o
	gcc -g -o teste3 huffman.o main3.o -lm

huffman.o: huffman.c
	gcc -g -o huffman.o -c huffman.c

main1.o: main1.c
	gcc -g -o main1.o -c main1.c

main2.o: main2.c
	gcc -g -o main2.o -c main2.c

main3.o: main3.c
	gcc -g -o main3.o -c main3.c

trie.o: trie.c
	gcc -g -o trie.o -c trie.c

clean:
	rm -f *.o

execClean:
	rm -f teste
