SRC = ./src
BIN = ./bin
INC = ./inc
LIB = ./lib
FLAGS = -std=c++11 -Wall
GCC = g++

all: lib $(SRC)/main.cpp
	$(GCC) $(FLAGS) $(SRC)/main.cpp $(LIB)/* -I $(INC) -o $(BIN)/main

lib: $(LIB)/Bomb.o \
	$(LIB)/Bug.o \
	$(LIB)/Game.o \
	$(LIB)/Gate.o \
	$(LIB)/Player.o \
	$(LIB)/Point.o \
	$(LIB)/Snippet.o \
	$(LIB)/Spawn.o \

$(LIB)/%.o : $(SRC)/%.cpp $(INC)/%.h
	$(GCC) $(FLAGS) -c $< -o $@ -I $(INC)

clean:
	rm $(BIN)/*
	rm $(LIB)/*

run:
	$(BIN)/main