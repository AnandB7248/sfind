CC = gcc
CFLAGS = -Wall -pedantic -g
MAIN = sfind
OBJS = main.o parseCommLine.o sfindUtil.o getPermission.o charArrayList.o
HEADER = parseCommLine.h sfindUtil.h getPermission.h charArrayList.h
all : $(MAIN)

$(MAIN) : $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

main.o : main.c parseCommLine.c parseCommLine.h
	$(CC) $(CFLAGS) -c main.c parseCommLine.c
parseCommLine.o : parseCommLine.c
	$(CC) $(CFLAGS) -c parseCommLine.c
sfindUtil.o : sfindUtil.c sfindUtil.h getPermission.c getPermission.h charArrayList.c charArrayList.h
	$(CC) $(CFLAGS) -c sfindUtil.c getPermission.c charArrayList.c
charArrayList.o : charArrayList.c charArrayList.h
	$(CC) $(CFLAGS) -c charArrayList.c 
getPermission.o : getPermission.c getPermission.h
	$(CC) $(CFLAGS) -c getPermission.c
clean : 
	rm *.o
