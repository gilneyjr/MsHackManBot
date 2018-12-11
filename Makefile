SRC = ./src
BIN = ./bin
INC = ./inc
OBJ = ./obj
FLAGS = -std=c++11 -Wall
GCC = g++

all: lib $(SRC)/main.cpp
	$(GCC) $(FLAGS) $(SRC)/main.cpp $(OBJ)/* -I $(INC) -o $(BIN)/main

lib: $(OBJ)/Bomb.o \
	$(OBJ)/Bug.o \
	$(OBJ)/Game.o \
	$(OBJ)/Player.o \
	$(OBJ)/Point.o \
	$(OBJ)/Snippet.o \
	$(OBJ)/Spawn.o \
	$(OBJ)/BehaviorTree.o \
	$(OBJ)/Composite.o \
	$(OBJ)/Action.o \
	$(OBJ)/Condition.o \
	$(OBJ)/Selector.o \
	$(OBJ)/Sequence.o \




$(OBJ)/%.o : $(SRC)/%.cpp $(INC)/%.h
	$(GCC) $(FLAGS) -c $< -o $@ -I $(INC)

clean:
	rm $(OBJ)/*
	rm $(BIN)/*

run:
	$(BIN)/main