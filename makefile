CC = g++
CPPFLAGS = -Iinclude `sdl2-config --cflags --libs`
CFLAGS = -Wall -pthread
LDLIBS = -lm -lpthread
SRC = src
OBJ = obj
MKDIR = mkdir -p

# Find all .cpp files in SRC recursively
SRCs := $(shell find $(SRC) -name "*.cpp")

# Map each .cpp file in SRC to a .o file in OBJ, preserving directory structure
OBJs := $(patsubst $(SRC)/%, $(OBJ)/%, $(SRCs:.cpp=.o))

# Build target: 'all' builds the final executable
all: main.o

# Link all object files into the final executable
main.o: $(OBJs)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDLIBS)

# Rule to compile each .cpp file to a .o file
$(OBJ)/%.o: $(SRC)/%.cpp
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Clean target to remove all generated files
clean:
	rm -rf $(OBJ) main.o
