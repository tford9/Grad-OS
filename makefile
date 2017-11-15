CFLAGS=-std=c++11 -Wall -O -g
CC=g++ 

BASECLASSOBJS=travBase.o cacheBase.o graphBase.o
DERIVEDCLASSOBJS=FIFOcache.o LIFOcache.o MRUcache.o RRcache.o LRUcache.o LFUcache.o OPTcache.o MLQcache.o traversals.o ListGraph.o MatrixGraph.o CompMatrixGraph.o

########## Base Class Objects ###########
sim: sim.o $(BASECLASSOBJS) $(DERIVEDCLASSOBJS)
	$(CC) $(CFLAGS) -o sim sim.o $(BASECLASSOBJS) $(DERIVEDCLASSOBJS)
sim.o: sim.cpp 
	$(CC) $(CFLAGS) -c sim.cpp 

########## Base Class Objects ###########
travBase.o: travBase.h travBase.cpp
	$(CC) $(CFLAGS) -c travBase.h travBase.cpp 
graphBase.o: graphBase.h graphBase.cpp
	$(CC) $(CFLAGS) -c graphBase.cpp graphBase.h
cacheBase.o: cacheBase.h cacheBase.cpp
	$(CC) $(CFLAGS) -c cacheBase.cpp cacheBase.h

########## Derived Class Objects ###########
FIFOcache.o: FIFOcache.h FIFOcache.cpp
	$(CC) $(CFLAGS) -c FIFOcache.cpp FIFOcache.h
RRcache.o: RRcache.h RRcache.cpp
	$(CC) $(CFLAGS) -c RRcache.cpp RRcache.h
LRUcache.o: LRUcache.h LRUcache.cpp
	$(CC) $(CFLAGS) -c LRUcache.cpp LRUcache.h
LFUcache.o: LFUcache.h LFUcache.cpp
	$(CC) $(CFLAGS) -c LFUcache.cpp LFUcache.h
LIFOcache.o: LIFOcache.h LIFOcache.cpp
	$(CC) $(CFLAGS) -c LIFOcache.cpp LIFOcache.h
MRUcache.o: MRUcache.h MRUcache.cpp
	$(CC) $(CFLAGS) -c MRUcache.cpp MRUcache.h
OPTcache.o: OPTcache.h OPTcache.cpp
	$(CC) $(CFLAGS) -c OPTcache.cpp OPTcache.h
MLQcache.o: MLQcache.h MLQcache.cpp
	$(CC) $(CFLAGS) -c MLQcache.cpp MLQcache.h
ListGraph.o: ListGraph.h ListGraph.cpp
	$(CC) $(CFLAGS) -c ListGraph.cpp ListGraph.h
MatrixGraph.o: MatrixGraph.h MatrixGraph.cpp
	$(CC) $(CFLAGS) -c MatrixGraph.cpp MatrixGraph.h
CompMatrixGraph.o: CompMatrixGraph.h CompMatrixGraph.cpp
	$(CC) $(CFLAGS) -c CompMatrixGraph.cpp CompMatrixGraph.h
traversals.o: traversals.h traversals.cpp
	$(CC) $(CFLAGS) -c traversals.cpp traversals.h

########## Housekeeping ###########
clean: 
	rm -f *.o *.gch core sim