all:ppm

ppm: ppm.o image_class.o
	g++ -o ppm ppm.o image_class.o

ppm.o: ppm.cpp image_class.h
	g++ -o ppm.o -c ppm.cpp -Wall

image_class.o: image_class.cpp image_class.h
	g++ -o image_class.o -c image_class.cpp -Wall

clean:
	rm -rf *.o

mrproper: clean
	rm -rf ppm