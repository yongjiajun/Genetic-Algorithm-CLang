CC = gcc
CCFLAGS = -Wall -ansi -pedantic
LIBS = -lm

all: ga 

debug: CCFLAGS += -DDEBUG
debug: ga

ga: drive.o invector.o pop.o gene.o
	$(CC) $(CCFLAGS) -o ga drive.o invector.o pop.o gene.o $(LIBS)

drive.o: drive.c drive.h 
	$(CC) $(CCFLAGS) -c drive.c $(LIBS)

gene.o: gene.c gene.h 
	$(CC) $(CCFLAGS) -c gene.c $(LIBS)

invector.o: invector.c invector.h
	$(CC) $(CCFLAGS) -c invector.c $(LIBS)

pop.o: pop.c pop.h
	$(CC) $(CCFLAGS) -c pop.c $(LIBS)

clean:
	rm ga *.o

