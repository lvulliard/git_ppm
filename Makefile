all:ppm

ppm: ppm.o image_class.o image_operations.o
	g++ -o ppm ppm.o image_class.o image_operations.o

ppm.o: ppm.cpp image_class.h image_operations.h
	g++ -o ppm.o -c ppm.cpp -Wall

image_class.o: image_class.cpp image_class.h
	g++ -o image_class.o -c image_class.cpp -Wall

image_operations.o: image_operations.cpp image_operations.h image_class.h
	g++ -o image_operations.o -c image_operations.cpp -Wall

clean:
	rm -rf *.o

mrproper: clean
	rm -rf ppm