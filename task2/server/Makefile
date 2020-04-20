IDIR = ./include
CC=gcc
ODIR = obj
CFLAGS=-I$(IDIR) 

_DEPS = db_server.h db_handling.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))  # return each string in _DEPS as IDIR/%.o 

_OBJ = db_server.o db_handling.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ)) # return each string in _OBJ as ODIR/%.o 

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -g

db_server: $(OBJ)  
	$(CC) -o $@ $^ $(CFLAGS) -lm -ljson-c