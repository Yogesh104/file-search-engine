all: FileSearch

FileSearch: hash_table.o generic_list.o main_indexer.o
	gcc -g -o FileSearch hash_table.o generic_list.o main_indexer.o

hash_table.o: hash_table.c hash.h
	gcc -g -c hash_table.c

generic_list.o: generic_list.c list.h
	gcc -g -c generic_list.c

main_indexer.o: main_indexer.c
	gcc -g -c main_indexer.c

clean:
	rm *.o
