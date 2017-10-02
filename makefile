CC=clang++
FLAGS=-std=c++11 -Wall -v
INCS=-I/usr/local/Cellar/boost/1.65.1 -I/usr/local/include
# LOCS=-L/usr/local/Cellar/boost/1.65.1/lib
LIBS=/usr/local/Cellar/boost/1.65.1/lib/libboost_program_options.a

# SOURCES=
# OBJECTS=$(SOURCES:.cpp=.o)

EXE=sim

all: simulator.o
	$(CC) $(FLAGS) $(INCS) $(LIBS) simulator.o -o $(EXE)

simulator.o : simulator.cpp utilities.o
	$(CC) $(FLAGS) -c simulator.cpp

utilities.o : utilities.cpp utilities.hpp
	$(CC) $(FLAGS) -c utilities.cpp utilities.hpp

clean: 
	rm *.o sim 
