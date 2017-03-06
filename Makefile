CC = gcc
CFLAGS = -Wall -pedantic -g
MAIN = sfind
OBJS = main.o parseCommLine.o sfindUtil.o getPermission.o charArrayList.o checked_fork.o limit_fork.o checked_open.o
HEADER = parseCommLine.h sfindUtil.h getPermission.h charArrayList.h checked_fork.h limit_fork.h checked_open.h
all : $(MAIN)

$(MAIN) : $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

main.o : main.c parseCommLine.c parseCommLine.h limit_fork.c limit_fork.h checked_open.c checked_open.h
	$(CC) $(CFLAGS) -c main.c parseCommLine.c limit_fork.c checked_open.c
parseCommLine.o : parseCommLine.c
	$(CC) $(CFLAGS) -c parseCommLine.c
sfindUtil.o : sfindUtil.c sfindUtil.h getPermission.c getPermission.h charArrayList.c charArrayList.h checked_fork.c checked_fork.h
	$(CC) $(CFLAGS) -c sfindUtil.c getPermission.c charArrayList.c
charArrayList.o : charArrayList.c charArrayList.h
	$(CC) $(CFLAGS) -c charArrayList.c 
getPermission.o : getPermission.c getPermission.h
	$(CC) $(CFLAGS) -c getPermission.c
checked_fork.o : checked_fork.c checked_fork.h
	$(CC) $(CFLAGS) -c checked_fork.c
limit_fork.o : limit_fork.c limit_fork.h
	$(CC) $(CFLAGS) -c limit_fork.c
checked_open.o : checked_open.c checked_open.h
	$(CC) $(CFLAGS) -c checked_open.c
clean : 
	rm *.o
