slave: bin/
	g++ -Wall -pthread -o bin/piNet slave/main.cpp -lpigpio -lrt

master:
	g++ -Wall -pthread -o bin/piNet master/main.cpp -lpigpio -lrt

bin_dir:
	mkdir bin/

obj_dir:
	mkdir obj/

clean:
	rm -rf bin/ obj/
