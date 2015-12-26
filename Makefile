DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin
DIR_TEST_SRC = ./test-src
DIR_TEST_OBJ = $(DIR_OBJ)/test
DIR_TEST_BIN = ./test-bin

INCLUDES=-I${DIR_INC}

CC  = gcc
CXX = g++

# CC=clang
# CXX=clang++

CFLAGS = -g -Wall -O2

############################################################
## UINT TEST

TEST_TARGETS = $(DIR_TEST_BIN)/test1

all: $(TEST_TARGETS)

$(DIR_TEST_BIN)/test1: $(DIR_TEST_OBJ)/test1.o $(DIR_OBJ)/readdisk.o
	$(CXX) -o $@ $(DIR_TEST_OBJ)/test1.o $(DIR_OBJ)/readdisk.o

$(DIR_TEST_OBJ)/test1.o: $(DIR_TEST_SRC)/test1.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(DIR_OBJ)/readdisk.o: $(DIR_SRC)/readdisk.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

##
############################################################

.PHONY:clean
clean:
	rm -f $(DIR_OBJ)/*.o \;
	rm -f $(DIR_TEST_OBJ)/*.o \;
	rm -f $(TEST_TARGETS) \;
