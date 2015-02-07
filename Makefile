CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic -g

all: ps2a

ps2a: test.o LFSR.o
	$(CC) $(FLAGS) -o ps2a test.o LFSR.o -lboost_unit_test_framework

test.o: test.cpp LFSR.cpp LFSR.hpp
	$(CC) $(FLAGS) -c test.cpp

LFSR.o: LFSR.cpp LFSR.hpp
	$(CC) $(FLAGS) -c LFSR.cpp

clean:
	rm -rf ps2a *.o *.~













