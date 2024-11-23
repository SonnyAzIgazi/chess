CC = g++
CPPFLAGS = -I../include `sdl2-config --cflags --libs` -nostartfiles
CFLAGS = -Wall -pthread
LDLIBS = -lm -lpthread
SRC = src
OBJ = obj
BIN = main
MKDIR = mkdir -p
SRCs := $(shell find $(SRC) -name "*.c")
OBJs := $(subst $(SRC), $(OBJ), $(SRCs:.c=.o))

all: $(BIN)

$(BIN): $(OBJs)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJs) -o $@ $(LDLIBS)

$(OBJs): $(SRCs)
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(subst $(OBJ), $(SRC), $(@:.o=.c)) -o $@
