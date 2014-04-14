CC = gcc -O0

CFLAGS = -Wall -Wextra

OBJS = netgen.o index.o random.o main.o

netgen: $(OBJS)
	$(CC) -o $@ $(CFLAGS) $(OBJS)

netgen.o: netgen.c
	$(CC) $(CFLAGS) $^ -c

index.o: index.c
	$(CC) $(CFLAGS) $^ -c

random.o: random.c
	$(CC) $(CFLAGS) $^ -c

main.o: main.c
	$(CC) $(CFLAGS) $^ -c

clean:
	rm *.o
