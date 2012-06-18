CC=gcc
CFLAGS=-g -Wall
CLIBS=ezxml/ezxml.o
OBJECTS=xmlgetf.o extract.o linked_list.o
OUTPUT=xmlgetf

%.o : %.c
	$(CC) $(CFLAGS) $(CLIBS) -c $<

all : xmlgetf.o linked_list.o extract.o
	$(CC) $(CFLAGS) $(CLIBS) $(OBJECTS) -o $(OUTPUT)

clean:
	rm $(OBJECTS) $(OUTPUT)