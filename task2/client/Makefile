IDIR = ./include
CC=gcc
ODIR = obj
CFLAGS=-I$(IDIR) 

_DEPS = db_client.h db_messages.h print_to_console.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))  # return each string in _DEPS as IDIR/%.o 

_OBJ = db_client.o db_messages.o print_to_console.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ)) # return each string in _OBJ as ODIR/%.o 

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -g

db_client: $(OBJ)  
	$(CC) -o $@ $^ $(CFLAGS) -lm -ljson-c