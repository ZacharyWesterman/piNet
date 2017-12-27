ZLIB = -I//home/pi/GitHub/zLibraries/
CFLAGS = -Wall -pthread
OBJFILES = main.o piNetworkRun.o network.node.o network.messageHandler.o

piNet: $(OBJFILES)
	g++ -lpigpio -lrt -o piNet $(OBJFILES)

main.o: main.cpp
	g++ -Wall -pthread $(ZLIB) -o main.o -c main.cpp

piNetworkRun.o: piNetworkRun.cpp
	g++ -Wall -o piNetworkRun.o -c piNetworkRun.cpp

network.node.o: network/node.cpp
	g++ -Wall $(ZLIB) -o network.node.o -c network/node.cpp

network.messageHandler.o: network/messageHandler.cpp
	g++ -Wall -pthread $(ZLIB) -o network.messageHandler.o -c network/messageHandler.cpp

clean:
	rm -rf *.o piNet
