# Source files
FILES = src/main.cpp

# Define libraries used in source
LINKER_FLAGS = -lSDL2

all:
	clang++ $(FILES) $(LINKER_FLAGS)