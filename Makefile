TARGET = jogo_palavras

CC = gcc

CFLAGS = -Wall -std=c11

OBJS = main.o jogo.o trie.o avl.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -lm

main.o: main.c trie.h avl.h
	$(CC) $(CFLAGS) -c main.c

jogo.o: jogo.c trie.h avl.h
	$(CC) $(CFLAGS) -c jogo.c

trie.o: trie.c trie.h
	$(CC) $(CFLAGS) -c trie.c

avl.o: avl.c avl.h
	$(CC) $(CFLAGS) -c avl.c

clean:
	rm -f $(OBJS) $(TARGET)