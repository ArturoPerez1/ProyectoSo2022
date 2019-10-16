CC=gcc
CFLAGS=-Wall
SRCDIR=src
BLDDIR=build

all: ucp timeprog

ucp: Ucp/$(SRCDIR)/ucp.c
	$(CC) $(CFLAGS) $^ -o Ucp/$(BLDDIR)/ucp

timeprog: Timeprog/$(SRCDIR)/timeprog.c
	$(CC) $(CFLAGS) $^ -o Timeprog/$(BLDDIR)/timeprog
