OUT = main
CC = gcc
ODIR = dist
SDIR = src
INC = -Isrc
LINK = -lwiringPi
CFLAGS = -g -Wall

_OBJS = dht11.o main.o

OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) $(LINK) -c $(INC) -o $@ $< $(CFLAGS)

$(OUT): $(OBJS)
	$(CC) $(OBJS) -Wall $(LINK) -o $@

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(OUT)
