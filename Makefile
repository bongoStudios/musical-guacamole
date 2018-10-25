CC = g++
CFLAGS = -g -Wall -fpermissive -std=c++11
LIBS = -lncurses -lpthread

all: rkprsc.cpp rkprsclzsk.cpp slotMachine.cpp cowrun.cpp dice.cpp random.hpp
	mkdir ./bin
	$(CC) $(CFLAGS) -o ./bin/rkprsc rkprsc.cpp $(LIBS)
	$(CC) $(CFLAGS) -o ./bin/rkprsclzsk rkprsclzsk.cpp $(LIBS)
	$(CC) $(CFLAGS) -o ./bin/slotMachine slotMachine.cpp $(LIBS)
	$(CC) $(CFLAGS) -o ./bin/cowrun cowrun.cpp $(LIBS)
	$(CC) $(CFLAGS) -o ./bin/dice dice.cpp $(LIBS)
	cp events.txt ./bin/

clean:
	$(RM) -r ./bin