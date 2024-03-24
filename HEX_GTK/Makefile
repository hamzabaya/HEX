# application name
TARGET=gtk

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS=    VersionGUI.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
    
VersionGUI.o: VersionGUI.c
	$(CC) -c $(CCFLAGS) VersionGUI.c $(GTKLIB) -o VersionGUI.o
    
clean:
	rm -f *.o $(TARGET)
