INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -lpthread
CFLAGS += -I$(INCLDIR)

OBJDIR = obj

#Headerfiles goes below
_DEPS = 
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

#Objectfiles goes below
_OBJS = oppgave-7-nettverk-server.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

oppgave7-server: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
