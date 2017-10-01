CC=g++
FLAGS=-std=c++14 -g

utilties : utilties.cpp
	$(CC) $(FLAGS) -o utilties utilties.cpp

clean: 
	rm -f utilties 
