INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -lm
CFLAGS += -I$(INCLDIR)

OBJDIR = obj

#Headerfiles goes below
_DEPS = 
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

#Objectfiles goes below
_OBJS = oppgave-4-finn-3-feil.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

oppgave4: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
