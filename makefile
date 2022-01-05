scarbble: main.o scrabble.o
	g++ -Wall -g main.o scrabble.o -o scrabble -std=c++11

main.o: main.cpp
	g++ -Wall -g -c main.cpp

scrabble.o: scrabble.cpp scrabble.h
	g++ -Wall -g -c scrabble.cpp

clean:
	rm -rf *.o scrabble