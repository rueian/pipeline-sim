CC=g++
CFLAGS=-Weverything

# MAIN properties
SRC=pipeline-simulation/src
SRC_MAIN_RUNNER_DIR=pipeline-simulation

all: clean compile

bin: clean-main compile

compile: clean-main prepare-main
	$(CC) $(SRC_MAIN_RUNNER_DIR)/*.cpp $(SRC)/CPU.cpp $(SRC)/Memory.cpp $(SRC)/Registers.cpp $(SRC)/Instruction.cpp $(SRC)/instruction/*.cpp -I$(SRC) -I$(SRC)/instruction -o simulate.out -std=c++11

clean:	clean-main

clean-main:
	rm -f simulate.out

prepare-main:
