all: output clean

output: huffman.o hash.o main_huffman.o
	gcc -g -o output huffman.o hash.o main_huffman.o -lm

huffman.o: huffman.c
	gcc -g -o huffman.o -c huffman.c

main_huffman.o: main_huffman.c
	gcc -g -o main_huffman.o -c main_huffman.c

hash.o: hash.c
	gcc -g -o hash.o -c hash.c

clean: 
	rm -f *.o

execClean:
	rm -f output