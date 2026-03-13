# Makefile to bootstrap mk without plan9port

CC = gcc
ROOT = $(shell pwd)/../../..
PREFIX = $(ROOT)/Linux/amd64

# Include paths
LIB9_SRC = ../lib/9
LIB9_INCLUDE = $(LIB9_SRC)/include
SYS_INCLUDE = ../../../sys/include

CFLAGS = -Wall -g -O2 -I$(LIB9_INCLUDE) -I$(SYS_INCLUDE) -I. \
         -DLINUX -D__amd64__ -D_POSIX_SOURCE -D_REENTRANT -D_GNU_SOURCE \
         -DROOT='"$(ROOT)"' -DUnix

LDFLAGS = -L$(LIB9_SRC) -L../lib/bio -L../lib/regexp
LDLIBS = -lregexp -lbio -llib9 -lpthread

SRC = main.c unix.c arc.c archive.c bufblock.c env.c file.c graph.c \
      job.c lex.c match.c mk.c parse.c recipe.c rc.c rule.c run.c \
      sh.c shell.c shprint.c symtab.c var.c varsub.c word.c

OBJ = $(SRC:.c=.o)
TARGET = mk
BINDIR = $(PREFIX)/bin

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	install -d $(BINDIR)
	install -m 755 $(TARGET) $(BINDIR)/

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all install clean
