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
EXAMPLE = $(DIR_BIN)/client
GENLIC  = $(DIR_BIN)/genlic

READDISK_LIBS=-lparted

all: $(TEST_TARGETS) $(EXAMPLE) $(GENLIC)

$(DIR_TEST_BIN)/test1: $(DIR_OBJ)/readdisk.o \
                  $(DIR_OBJ)/mypipe.o \
                  $(DIR_OBJ)/des.o \
                  $(DIR_OBJ)/base64.o \
                  $(DIR_OBJ)/serialno.o \
                  $(DIR_TEST_OBJ)/test1.o 
	$(CXX) -o $@ $(DIR_OBJ)/readdisk.o \
                  $(DIR_OBJ)/mypipe.o \
                  $(DIR_OBJ)/des.o \
                  $(DIR_OBJ)/base64.o \
                  $(DIR_OBJ)/serialno.o \
                  $(DIR_TEST_OBJ)/test1.o \
                  $(READDISK_LIBS)

$(EXAMPLE): $(DIR_OBJ)/readdisk.o \
            $(DIR_OBJ)/mypipe.o \
            $(DIR_OBJ)/des.o \
            $(DIR_OBJ)/base64.o \
            $(DIR_OBJ)/serialno.o \
            $(DIR_OBJ)/client.o
	$(CC) -o $@ $(DIR_OBJ)/readdisk.o \
                    $(DIR_OBJ)/mypipe.o \
                    $(DIR_OBJ)/des.o \
                    $(DIR_OBJ)/base64.o \
                    $(DIR_OBJ)/serialno.o \
                    $(DIR_OBJ)/client.o \
                    $(READDISK_LIBS)

$(GENLIC):  $(DIR_OBJ)/readdisk.o \
            $(DIR_OBJ)/mypipe.o \
            $(DIR_OBJ)/des.o \
            $(DIR_OBJ)/base64.o \
            $(DIR_OBJ)/serialno.o \
            $(DIR_OBJ)/genlic.o
	$(CC) -o $@ $(DIR_OBJ)/readdisk.o \
                    $(DIR_OBJ)/mypipe.o \
                    $(DIR_OBJ)/des.o \
                    $(DIR_OBJ)/base64.o \
                    $(DIR_OBJ)/serialno.o \
                    $(DIR_OBJ)/genlic.o \
                    $(READDISK_LIBS)

$(DIR_OBJ)/readdisk.o: $(DIR_SRC)/readdisk.c $(DIR_INC)/readdisk.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(DIR_OBJ)/mypipe.o: $(DIR_SRC)/mypipe.c $(DIR_INC)/mypipe.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(DIR_OBJ)/des.o: $(DIR_SRC)/des.c $(DIR_INC)/des.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(DIR_OBJ)/base64.o: $(DIR_SRC)/base64.c $(DIR_INC)/base64.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(DIR_OBJ)/serialno.o: $(DIR_SRC)/serialno.c $(DIR_INC)/serialno.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(DIR_OBJ)/client.o: $(DIR_SRC)/client.c $(DIR_INC)/readdisk.h  $(DIR_INC)/serialno.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(DIR_OBJ)/genlic.o: $(DIR_SRC)/genlic.c $(DIR_INC)/readdisk.h  $(DIR_INC)/serialno.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(DIR_TEST_OBJ)/test1.o: $(DIR_TEST_SRC)/test1.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDES)


##
############################################################

.PHONY:clean
clean:
	rm -f $(DIR_OBJ)/*.o \;
	rm -f $(DIR_TEST_OBJ)/*.o \;
	rm -f $(TEST_TARGETS) \;
	rm -f $(EXAMPLE) $(GENLIC) \;
