INCLUDE = /home/pi/GitHub/zLibraries/

piNet: main.o
	g++ -lpigpio -lrt -o piNet main.o

main.o: main.cpp
	g++ -Wall -pthread -I/$(INCLUDE) -o main.o -c main.cpp

clean:
	rm -rf *.o piNet
