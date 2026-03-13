# Makefile to bootstrap rc without plan9port
# 64-bit build for amd64

CC = gcc
ROOT = $(shell pwd)/../../..
PREFIX = $(ROOT)/Linux/amd64

# Include paths - lib/9 and bio are sibling directories
LIB9_SRC = ../lib/9
LIB9_INCLUDE = $(LIB9_SRC)/include
SYS_INCLUDE = ../../sys/include

CFLAGS = -Wall -g -O2 -I$(LIB9_INCLUDE) -I$(SYS_INCLUDE) -I. \
         -DLINUX -D__amd64__ -D_POSIX_SOURCE -D_REENTRANT -D_GNU_SOURCE -fPIC \
         -DLINUX_AMD64 -DROOT='"$(ROOT)"' -DUnix

LDFLAGS = -L$(LIB9_SRC) -L../lib/bio
LDLIBS = -lbio -llib9 -lpthread

# Source files
SRC = code.c exec.c getflags.c glob.c globals.c here.c io.c lex.c \
      pcmd.c pfnc.c simple.c subr.c trap.c tree.c var.c \
      havefork.c unix.c y.tab.c

OBJ = $(SRC:.c=.o)
TARGET = rc
BINDIR = $(PREFIX)/bin

# Default target - must be first
all: $(TARGET)

# All object files depend on y.tab.h
$(OBJ): y.tab.h

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

y.tab.c y.tab.h: syn.y
	bison -y -d syn.y || yacc -d syn.y

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	install -d $(BINDIR)
	install -m 755 $(TARGET) $(BINDIR)/

clean:
	rm -f $(OBJ) $(TARGET) y.tab.c y.tab.h

.PHONY: all install clean
