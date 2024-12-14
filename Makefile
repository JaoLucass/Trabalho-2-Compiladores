# Makefile para compilação em ambiente Linux ou Codespaces
CC = g++
CFLAGS = -std=c++11 -Wall -g
SRC = main.cpp symtable.cpp error.cpp lexer.cpp parser.cpp
OBJ = $(SRC:.cpp=.o)
BIN = simbolos

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)