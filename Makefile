CC=g++ 

CFLAGS=-c 

all: diff

diff: main.o DifFunctions.o
	$(CC) main.o DifFunctions.o -o diff

main.o: main.cpp 
	$(CC) $(CFLAGS) main.cpp  -o main.o

DifFunctions.o: DifFunctions.cpp
	$(CC) $(CFLAGS) DifFunctions.cpp  -o DifFunctions.o

clean: 
	rm -rf *.o diff