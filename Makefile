CC = gcc
CFLAGS = -Wall -pedantic
MAIN = sfind
OBJS = main.o parseCommLine.o
HEADER = parseCommLine.h
all : $(MAIN)

$(MAIN) : $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

main.o : main.c parseCommLine.c parseCommLine.h
	$(CC) $(CFLAGS) -c main.c parseCommLine.c
parseCommLine.o : parseCommLine.c
	$(CC) $(CFLAGS) -c parseCommLine.c

clean : 
	rm *.o
