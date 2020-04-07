IDIR = ./include
CC=gcc
ODIR = obj
CFLAGS=-I$(IDIR)
SRCDIR=

_DEPS = signal_gen.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS)) # return each string in _DEPS as IDIR/%.o 

_OBJ = signal_gen.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ)) # return each string in _OBJ as ODIR/%.o 

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

signal_gen: $(OBJ)  
	$(CC) -o $@ $^ $(CFLAGS) 