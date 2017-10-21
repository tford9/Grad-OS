CFLAGS = -O 
CC = g++ 
sim: sim.o utils.o travBase.o cacheBase.o graphBase.o
	$(CC) $(CFLAGS) -o sim sim.o utils.o travBase.o cacheBase.o graphBase.o
	
sim.o: sim.cpp 
	$(CC) $(CFLAGS) -c sim.cpp 
travBase.o: travBase.h
	$(CC) $(CFLAGS) -c travBase.h travBase.cpp 
graphBase.o: graphBase.h graphBase.cpp
	$(CC) $(CFLAGS) -c graphBase.cpp 
cacheBase.o: cacheBase.h cacheBase.cpp
	$(CC) $(CFLAGS) -c cacheBase.cpp
utils.o: utils.cpp
	$(CC) $(CFLAGS) -c utils.cpp
clean: 
	rm -f core *.o *.gcf 
