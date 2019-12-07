CC=gcc
CFLAGS=-Wall
SRCDIR=src
BLDDIR=build

all: ucp timeprog fibo

ucp: Ucp/$(SRCDIR)/ucp.c
	$(CC) $(CFLAGS) $^ -o Ucp/$(BLDDIR)/ucp

timeprog: Timeprog/$(SRCDIR)/timeprog.c
	$(CC) $(CFLAGS) $^ -o Timeprog/$(BLDDIR)/timeprog

fibo: Fibo/$(SRCDIR)/fibo.c
	$(CC) $(CFLAGS) $^ -o Fibo/$(BLDDIR)/fibo

sigalarm: sigalarm/$(SRCDIR)/sigalarm.c
	$(CC) $(CFLAGS) $^ -o sigalarm/$(BLDDIR)/sigalarm
