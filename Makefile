ZLIB = -I//home/pi/GitHub/zLibraries/
OBJFILES = main.o piNetworkRun.o network.node.o network.messageHandler.o network.messageList.o network.message.o

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
	
network.messageList.o: network/messageList.cpp
	g++ -Wall -o network.messageList.o -c network/messageList.cpp
	
network.message.o: network/message.cpp
	g++ -Wall -o network.message.o -c network/message.cpp

clean:
	rm -rf *.o piNet
