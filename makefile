CC = gcc
AR = ar
FLAGS = -Wall -g

alL: frequency
frequency: Trie.c
	$(CC) $(FLAGS) Trie.c -o frequency
clean:
	rm frequency
.PHONY: clean all