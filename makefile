CC := gcc -O0

CFLAGS := -Wall -Wextra

OBJS := netgen.o index.o random.o main.o
TARGET := ./bin/netgen

$(TARGET): $(OBJS)
	@echo "Linking... "
	$(CC) $^ -o $@ $(CFLAGS)
	@echo "Cleaning..."
	rm *.o

netgen.o: src/netgen.c
	$(CC) $(CFLAGS) $^ -c

index.o: src/index.c
	$(CC) $(CFLAGS) $^ -c

random.o: src/random.c
	$(CC) $(CFLAGS) $^ -c

main.o: src/main.c
	$(CC) $(CFLAGS) $^ -c

clean:
	rm *.o
