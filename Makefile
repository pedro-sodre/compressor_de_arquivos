all: output clean

output: huffman.o main_huffman.o
	gcc -o output huffman.o main_huffman.o

huffman.o: huffman.c
	gcc -o huffman.o -c huffman.c

main_huffman.o: main_huffman.c
	gcc -o main_huffman.o -c main_huffman.c

clean: 
	rm -f *.o

execClean:
	rm -f output