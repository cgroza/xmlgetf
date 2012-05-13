CC=gcc
CFLAGS=-g -O2 -Wall
CLIBS=ezxml/ezxml.o
OBJECTS=xmlgetf.o
OUTPUT=xmlgetf

%.o : %.c
	$(CC) $(CFLAGS) $(CLIBS) -c $<

all : xmlgetf.o
	$(CC) $(CFLAGS) $(CLIBS) $(OBJECTS) -o $(OUTPUT)

clean:
	rm $(OBJECTS) $(OUTPUT)