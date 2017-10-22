CFLAGS=-std=c++11 -Wall -v -O
CC=g++ 

BASECLASSOBJS=travBase.o cacheBase.o graphBase.o
DERIVEDCLASSOBJS=cacheReplacementPolicy.o traversals.o

########## Base Class Objects ###########
sim: sim.o utils.o $(BASECLASSOBJS) $(DERIVEDCLASSOBJS)
	$(CC) $(CFLAGS) -o sim sim.o utils.o $(BASECLASSOBJS) $(DERIVEDCLASSOBJS)
sim.o: sim.cpp 
	$(CC) $(CFLAGS) -c sim.cpp 

########## Base Class Objects ###########
travBase.o: travBase.h
	$(CC) $(CFLAGS) -c travBase.h travBase.cpp 
graphBase.o: graphBase.h graphBase.cpp
	$(CC) $(CFLAGS) -c graphBase.cpp 
cacheBase.o: cacheBase.h cacheBase.cpp
	$(CC) $(CFLAGS) -c cacheBase.cpp

########## Derived Class Objects ###########
cacheReplacementPolicy.o: cacheReplacementPolicy.h cacheReplacementPolicy.cpp
	$(CC) $(CFLAGS) -c cacheReplacementPolicy.cpp cacheReplacementPolicy.h

traversals.o: traversals.h 
	$(CC) $(CFLAGS) -c traversals.cpp traversals.h
########## Utilities ###########
utils.o: utils.cpp
	$(CC) $(CFLAGS) -c utils.cpp

########## Housekeeping ###########
clean: 
	rm -f *.o *.gch core sim
