CC = g++ -std=c++0x
CFLAGS = -Wall -Werror -ansi -pedantic -g

all: PhotoMagic

PhotoMagic: PhotoMagic.o LFSR.o
	$(CC) $(FLAGS) -o PhotoMagic PhotoMagic.o LFSR.o -lsfml-graphics -lsfml-window -lsfml-system

PhotoMagic.o: PhotoMagic.cpp LFSR.cpp LFSR.hpp
	$(CC) $(FLAGS) -c PhotoMagic.cpp

LFSR.o: LFSR.cpp LFSR.hpp
	$(CC) $(FLAGS) -c LFSR.cpp

clean:
	rm -rf PhotoMagic *.o *.~


