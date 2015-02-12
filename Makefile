CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic -g

all: PhotoMagic

PhotoMagic: PhotoMagic.o LFSR.o
	$(CC) $(FLAGS) -o PhotoMagic PhotoMagic.o LFSR.o -lboost_unit_test_framework

PhotoMagic.o: PhotoMagic.cpp LFSR.cpp LFSR.hpp
	$(CC) $(FLAGS) -c PhotoMagic.cpp

LFSR.o: LFSR.cpp LFSR.hpp
	$(CC) $(FLAGS) -c LFSR.cpp

clean:
	rm -rf PhotoMagic *.o *.~


