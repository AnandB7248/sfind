CC = gcc
CFLAGS = -Wall -pedantic -g
MAIN = sfind
OBJS = main.o parseCommLine.o sfindUtil.o getPermission.o charArrayList.o checked.o limit_fork.o
HEADER = parseCommLine.h sfindUtil.h getPermission.h charArrayList.h limit_fork.h checked.h
all : $(MAIN)

$(MAIN) : $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

main.o : main.c parseCommLine.c parseCommLine.h limit_fork.c limit_fork.h checked.c checked.h
	$(CC) $(CFLAGS) -c main.c parseCommLine.c limit_fork.c checked.c
parseCommLine.o : parseCommLine.c
	$(CC) $(CFLAGS) -c parseCommLine.c
sfindUtil.o : sfindUtil.c sfindUtil.h getPermission.c getPermission.h charArrayList.c charArrayList.h checked.c checked.h
	$(CC) $(CFLAGS) -c sfindUtil.c getPermission.c charArrayList.c checked.c
charArrayList.o : charArrayList.c charArrayList.h
	$(CC) $(CFLAGS) -c charArrayList.c 
getPermission.o : getPermission.c getPermission.h
	$(CC) $(CFLAGS) -c getPermission.c
checked.o : checked.c checked.h
	$(CC) $(CFLAGS) -c checked.c
limit_fork.o : limit_fork.c limit_fork.h
	$(CC) $(CFLAGS) -c limit_fork.c
clean : 
	rm *.o
