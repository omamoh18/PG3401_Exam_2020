INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)

OBJDIR = obj

#Headerfiles goes below
_DEPS = 
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

#Objectfiles goes below
_OBJS = oppgave-5-filhåndtering.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

oppgave5: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
