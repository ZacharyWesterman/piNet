slave:
	mkdir bin/
	g++ -Wall -pthread -o bin/piNet slave/main.cpp -lpigpio -lrt

master:
	mkdir bin/
	g++ -Wall -pthread -o bin/piNet master/main.cpp -lpigpio -lrt

clean:
	rm -rf bin/ obj/
