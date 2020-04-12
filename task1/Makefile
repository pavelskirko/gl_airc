IDIR = ./include
CC=gcc
ODIR = obj
CFLAGS=-I$(IDIR)
SRCDIR=

_DEPS = get_user_input.h signal_gen.h  io.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))  # return each string in _DEPS as IDIR/%.o 

_OBJ = signal_gen.o get_user_input.o io.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ)) # return each string in _OBJ as ODIR/%.o 

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -g

signal_gen: $(OBJ)  
	$(CC) -o $@ $^ $(CFLAGS) -lm