CC=clang++
FLAGS=-std=c++11
# INCS=-I/usr/local/Cellar/boost/1.64.0_1
# LOCS=-L/usr/local/Cellar/boost/1.64.0_1/lib
LIBS=-lboost_program_options

sim : simulator.cpp
	$(CC) $(FLAGS) simulator.cpp -o sim $(LIBS)

utilties : utilties.cpp
	$(CC) $(FLAGS) -o utilties utilties.cpp

clean: 
	rm -f sim 
